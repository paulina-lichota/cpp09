/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 23:19:39 by plichota          #+#    #+#             */
/*   Updated: 2026/03/11 18:26:47 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <ctime>

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

  return 1;
}

// return 1 if rate is valid, 0 otherwise
static int isValidRate(const std::string& rate)
{
  // check if rate is a valid float or a positive integer between 0 and 1000
  try {
    size_t i = 0;
    // stod assegna a i il primo indice non utilizzato es. 1234a restituisce indice di a
    // se fallisce lancia exception
    double d = std::stod(rate, &i);
    // ci sono caratteri extra dopo il numero
    if (i != rate.length())
      return 0;
    // non compresi tra 0 e 1000
    if (d < 0 || d > 1000)
      return 0;
  }
  catch (const std::exception& e) {
    return 0;
  }
  return 1;
}

// "date | value"
// map automatically orders by date due to > operator on std::string
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
    double rate = std::stod(value);
    // _db[date] = rate; // METODO 1
    _db.insert(std::make_pair(date, rate)); // METODO 2
  }
}

double BitcoinExchange::getRate(const std::string& date) const
{
  // check date is valid
  // check date is in db
  // if not, find closest date before it
}