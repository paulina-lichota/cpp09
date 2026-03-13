/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 19:11:29 by plichota          #+#    #+#             */
/*   Updated: 2026/03/13 19:20:43 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>
#include <string>

// The management of errors related to duplicates is left to your discretion

int main(int argc, char **argv)
{
  if (argc < 2)
  {
    std::cerr << "Usage: " << argv[0] << " <numbers...>" << std::endl;
    return 1;
  }
  // check if args are POSITIVE INTEGERS
  // merge-insert sort algorithm

  // 1 print before
  // 2 print after
  // 3 Time to process a range of 5 elements with std::<container1> : 0.00031 us
  // 4 Time to process a range of 5 elements with std::<container1> : 0.00031 us
  
  // try with at least 3000 elements
}