/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 23:19:39 by plichota          #+#    #+#             */
/*   Updated: 2026/03/11 22:31:25 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
/*
  Includo queste librerie solo nel .cpp perche' 
   riduco il tempo di compilazione e rischio di conflitti.
  Il .cpp viene compilato solo una volta, mentre l'header viene compilato
   ogni volta che viene incluso in un altro file.
*/
#include <string>
#include <cstdlib> // atoi
#include <cctype> // isdigit
#include <sstream> // stringstream

BitcoinExchange::BitcoinExchange() : _db() {}

BitcoinExchange::BitcoinExchange(const std::string& filename) : _db()
{
  loadDatabase(filename);
}
BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _db(other._db) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
  if (this != &other)
    _db = other._db;
  return *this;
}

BitcoinExchange::~BitcoinExchange() {}

/* ======================================================================== */
/*                              H E L P E R S                               */
/* ======================================================================== */

static void trimString(std::string& str)
{
  // restituisce indice del primo carattere che non e' uno spazio
  size_t first = str.find_first_not_of(" \t\n\r\f\v");
  // se non trova nulla (non esiste carattere oltre a spazi), return
  if (first == std::string::npos)
    return;
  str.erase(0, first);
  // restituisce indice dell'ultimo carattere che non e' uno spazio
  size_t last = str.find_last_not_of(" \t\n\r\f\v");
  if (last == std::string::npos)
    return;
  // se non specifico il numero di caratteri, rimuove tutti da last in poi
  // se last e' ultimo carattere, last + 1 corrisponde a fine stringa, quindi chiamata sicura
  str.erase(last + 1);
}

static void printError(const std::string& line)
{
  std::cerr << MAGENTA << "Error: " << line << RESET << std::endl;
}

/* ======================================================================== */
/*                              V A L I D A T E                             */
/* ======================================================================== */

// check format "YYYY-MM-DD"
// 2013-024-12 DOES NOT COUNT as valid date
static int isValidDate(const std::string& date)
{
  // std:: cout << "Validating date: " << BLUE << date << RESET << std::endl;
  if (date.length() != 10)
    return (0);

  for (size_t i = 0; i < 10; i++)
  {
    if ((i == 4 || i == 7))
    {
      if (date[i] != '-') return 0;
    }
    else if (!isdigit(date[i])) return 0;
  }

  // check valid month and day
  int y = std::atoi(date.substr(0, 4).c_str());
  int m = std::atoi(date.substr(5, 2).c_str());
  int d = std::atoi(date.substr(8, 2).c_str());
  if (m < 1 || m > 12 || d < 1 || d > 31 || y < 2009)
  {
    std::cerr << MAGENTA << "Error: bad input => " << date << RESET << std::endl;
    return 0;
  }

  // altri controlli su giorni per mese e anni bisestili potrebbero essere aggiunti, ma non richiesti
  // potrei usare mktime per controllare che la data sia realmente valida

  return 1;
}

// return 1 if rate is valid, 0 otherwise
static int isValidRate(const std::string& rate)
{
  double d;
  char c;
  // creo oggetto stringstream che contiene la stringa
  std::stringstream ss(rate);
  
  /*
    leggo un double dallo stream
    man mano che legge il "puntatore interno" avanza finche' riconosce sequenza del double
    - se la lettura va a buon fine, restituice una reference allo stream (true)
    - altrimenti lo stream imposta una flag (failbit), restituitendo false
  */
  if (!(ss >> d))
  {
    std::cerr << MAGENTA << "Error: invalid rate format." << RESET << std::endl;
    return 0;
  }
  // no extra chars after number
  if (ss >> c)
    return 0;
  // valid range (according to subject)
  if (d < 0)
  {
    std::cerr << MAGENTA << "Error: not a positive number." << RESET << std::endl;
    return 0;
  }
  if (d > 1000)
  {
    std::cerr << MAGENTA << "Error: too large a number." << RESET << std::endl;
    return 0;
  }
  return 1;
}

/* ======================================================================== */
/*                              L O A D E R S                               */
/* ======================================================================== */

  /*
    INSERTING INTO MAP:
    map automatically orders by date (due to > operator on std::string)
    Usa il black red tree quindi bilancia automaticamente:
    - inserimento, cancellazione e ricerca in (O(log n))

    METODO 1
    se chiave esiste, aggiorna valore
    _db[date] = rate;

    METODO 2
    se chiave esiste, NON aggiorna valore
    _db.insert(std::make_pair(date, rate));

    METODO 3
    se chiave esiste, NON aggiorna valore
    inserisce direttamente all'interno della mappa senza creare copie temporanee
    piu' efficiente con tipi complessi, in questo caso non e' necessario
    _db.emplace("key", 42);
  */

void BitcoinExchange::loadDatabase(const std::string& filename)
{
  // std::cout << BLUE << "Loading database: " << filename << RESET << std::endl;
  if (filename.length() == 0 || filename.substr(filename.length() - 4) != ".csv")
  {
    std::cerr << MAGENTA << "Error: invalid database filename." << RESET << std::endl;
    return;
  }
  
  std::ifstream file(filename.c_str());
  if (!file.is_open())
  {
    std::cerr << MAGENTA << "Error: could not open database file." << RESET << std::endl;
    return;
  }
  std::string l;

  // skippo intestazione
  std::getline(file, l);
  if (l != "date,exchange_rate")
  {
    std::cerr << MAGENTA << "DB Error: invalid database header." << RESET << std::endl;
    return;
  }
  
  while (std::getline(file, l))
  {
    // std:: cout << "Parsing line: " << YELLOW << l << RESET << std::endl;
    if (l.find(",") == std::string::npos)
    {
      std::cerr << MAGENTA << "DB Error: invalid line format." << RESET << std::endl;
      continue;
    }
    std::string date = l.substr(0, l.find(","));
    trimString(date);
    if (!isValidDate(date))
      continue; // salta al ciclo successivo
    std::string value = l.substr(l.find(",") + 1); // prende fino al '\0'
    std::stringstream ss(value);
    double rate;
    if (!(ss >> rate))
    {
      std::cerr << MAGENTA << "DB Error: invalid rate, not a valid number." << RESET << std::endl;
      continue;
    }
    _db.insert(std::make_pair(date, rate)); // _db[date] = rate; se voglio sovrascrivere eventuali duplicati
  }
}

/* ======================================================================== */
/*                            P R O C E S S                                 */
/* ======================================================================== */

  /*
    per accedere ai dati dentro mappa si usano metodi
    key: it->first
    value: it->second
  */

// search for date in database
// if not found, return closest date before
double BitcoinExchange::getRate(const std::string& date) const
{
  // cercare data esatta
  std::map<std::string, double>::const_iterator it = _db.find(date);
  if (it != _db.end())
    return it->second;

  // cerco data piu' vicina minore piu' vicina a quella richiesta
  it = _db.lower_bound(date); // returns the first key that is equal or greater than k
  if (it != _db.begin())
  {
    --it; // vai alla data immediatamente precedente
    return it->second; // ritorno value
  }
  // nessuna data precedente trovata
  return 0.0;
}

void BitcoinExchange::processFile(const std::string& filename)
{
  // std::cout << BLUE << "Processing file: " << filename << RESET << std::endl;
  std::ifstream inputFile(filename.c_str());
  if (!inputFile.is_open())
  {
    std::cerr << "Error: could not open file." << std::endl;
    return;
  }

  std::string l;
  std::getline(inputFile, l);
  if (l != "date | value")
  {
    std::cerr << "Error: invalid input header." << std::endl;
    return;
  }
  while (std::getline(inputFile, l))
  {
    // std:: cout << "Parsing line: " << YELLOW << l << RESET << std::endl;
    if (l.find("|") == std::string::npos)
    {
      printError("bad input => " + l);
      continue;
    }
    std::string date = l.substr(0, l.find("|"));
    trimString(date);
    if (!isValidDate(date))
    {
      printError("invalid date format: " + date);
      continue;
    }
    std::string value = l.substr(l.find("|") + 1); // prende fino al '\0'
    trimString(value);
    // std:: cout << "Parsing rate: " << YELLOW << value << RESET << std::endl;
    if (!isValidRate(value))
      continue;
    std::stringstream ss(value);
    double rate;
    if (!(ss >> rate))
    {
      printError("invalid rate, not a valid number");
      continue;
    }
    std::cout << date << " => " << rate << " => " << YELLOW << rate *getRate(date) << RESET << std::endl;
  }
}

/* ======================================================================== */
/*                               D E B U G                                  */
/* ======================================================================== */

void BitcoinExchange::printDatabase() const
{
  std::cout << "Database:" << std::endl;
  std::map<std::string, double>::const_iterator it = _db.begin();
  for (; it != _db.end(); ++it) {
    std::cout << "Data: " << it->first << ", Rate: " 
      << YELLOW << it->second << RESET << std::endl;
  }
}
