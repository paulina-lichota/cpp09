/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 23:19:39 by plichota          #+#    #+#             */
/*   Updated: 2026/03/11 19:01:21 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
/*
  Includo queste librerie solo nel .cpp perche' 
   riduco il tempo di compilazione e rischio di conflitti.
  Il .cpp viene compilato solo una volta, mentre l'header viene compilato
   ogni volta che viene incluso in un altro file.
*/
#include <ctime>
#include <cstdlib>

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

static int isValidDate(const std::string& date)
{
  // check format YYYY-MM-DD
  if (date.length() != 10)
    return 0;
  size_t i = 0;
  while (i < 4)
  {
    if (date[i] < '0' || date[i] > '9')
      return 0;
    i++;
  }
  if (date[4] != '-')
    return 0;
  while (i < 7)
  {
    if (date[i] < '0' || date[i] > '9')
      return 0;
    i++;
  }
  if (date[7] != '-')
    return 0;
  while (i < 10)
  {
    if (date[i] < '0' || date[i] > '9')
      return 0;
    i++;
  }

  // check valid month and day
  int y = std::atoi(date.substr(0, 4).c_str());
  int m = std::atoi(date.substr(5, 2).c_str());
  int d = std::atoi(date.substr(8, 2).c_str());
  if (m < 1 || m > 12 || d < 1 || d > 31)
    return 0;

  // altri controlli su giorni per mese e anni bisestili potrebbero essere aggiunti, ma non richiesti
  // uso mktime per controllare che la data sia realmente valida
  (void) y;

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
    > se la lettura va a buon fine, restituice una reference allo stream (true)
    > altrimenti lo stream imposta una flag (failbit), restituitendo false
  */
  if (!(ss >> d))
    return 0;
  // no extra chars after number
  if (ss >> c)
    return 0;
  // valid range (according to subject)
  if (d < 0 || d > 1000)
    return 0;
  return 1;
}

void BitcoinExchange::loadDatabase(const std::string& filename)
{
  std::ifstream file(filename.c_str());
  if (!file.is_open())
  {
    std::cerr << "Error: could not open database file." << std::endl;
    return;
  }
  std::string l;
  while (std::getline(file, l))
  {
    if (l.find(",") == std::string::npos)
    {
      std::cerr << "Error: invalid line format." << std::endl;
      return;
    }
    std::string date = l.substr(0, l.find(","));
    if (!isValidDate(date))
    {
      std::cerr << "Error: invalid date format." << std::endl;
      return;
    }
    std::string value = l.substr(l.find(",") + 1); // prende fino al '\0'
    if (!isValidRate(value))
    {
      std::cerr << "Error: invalid rate format." << std::endl;
      return;
    }
    // (validation gia' fatta)
    std::stringstream ss(value);
    double rate;
    ss >> rate;
    /*
      INSERTING INTO MAP:
      map automatically orders by date (due to > operator on std::string)
      Usa il black red tree quindi bilancia automaticamente:
      - inserimento, cancellazione e ricerca in (O(log n))
    */
    /* 
      METODO 1
      se chiave esiste, aggiorna valore
      _db[date] = rate;
    */
    /*
      METODO 2
      se chiave esiste, NON aggiorna valore
      _db.insert(std::make_pair(date, rate));
    */
    _db.insert(std::make_pair(date, rate));
  }
}

double BitcoinExchange::getRate(const std::string& date) const
{
  (void) date;
  // check date is valid
  // check date is in db
  // if not, find closest date before it
  return 0.0;
}