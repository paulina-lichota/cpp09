/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 14:19:01 by plichota          #+#    #+#             */
/*   Updated: 2026/03/20 16:06:40 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

#include <string>
#include <iostream>
#include <vector>

// The management of errors related to duplicates is left to your discretion.

int parse_args(int argc, char **argv, std::vector<int>& numbers)
{
    for (int i = 1; i < argc; i++)
    {
        // parse
        numbers.push_back(std::atoi(argv[i]));
    }
    return 0;
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <numbers...>" << std::endl;
        return 1;
    }
    std::vector<int> numbers;
    if (parse_args(argc, argv, numbers))
    {
        std::cerr << "Error: invalid arguments" << std::endl;
        return 1;
    }

    //init constructor
    PmergeMe x(numbers);
    x.print();
    // sort numbers vector
    // // sort numbers deque
    // print after sorting
    // print time The indication of the time is deliberately strange in this example.
        // Of course you have to indicate the time used to perform all your
        // operations, both the sorting part and the data management part.
    // print time
}