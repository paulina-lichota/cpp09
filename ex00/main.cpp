/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 23:19:58 by plichota          #+#    #+#             */
/*   Updated: 2026/03/11 19:05:55 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <string>

// returns 0 un success, 1 on error
int parseFilename(const std::string& filename)
{
  std::ifstream file(filename.c_str());
  if (!file.is_open())
    return 1;
  // closes file when it goes out of scope
  return 0;
}

int main(int argc, char **argv)
{
  if (argc != 2 || parseFilename(argv[1]) != 0)
  {
    std::cerr << "Error: could not open file." << std::endl;
    return 1;
  }
  std::ifstream inputFile(argv[1]);
  ::BitcoinExchange btc("data.csv");
  btc.printDatabase();
  return 0;
}