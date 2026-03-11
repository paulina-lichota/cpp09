/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 23:19:39 by plichota          #+#    #+#             */
/*   Updated: 2026/03/11 00:44:34 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

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
    // parse line and insert into _db
    _db[date] = value;
    _db.insert(std::make_pair(date, value));
  }
}

float BitcoinExchange::getRate(const std::string& date) const
{
  // check date is valid
  // check date is in db
  // if not, find closest date before it
}