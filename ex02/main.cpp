/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 14:19:01 by plichota          #+#    #+#             */
/*   Updated: 2026/03/20 17:12:30 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

#include <string>
#include <iostream>
#include <vector>
#include <cstring> // strlen
#include <cstdlib> // atoi
#include <limits> // numeric_limits

// The management of errors related to duplicates is left to your discretion.

// 0 parsing ok, 1 otherwise
// only positive integers
int parse_args(int argc, char **argv, std::vector<int>& numbers)
{
    for (int i = 1; i < argc; i++)
    {
        // max length of int 2147483648 (10 digits)
        if (std::strlen(argv[i]) > 10)
            return 1;
        // parse single char
        for (int j = 0; argv[i][j] != '\0'; j++)
        {
            if (!std::isdigit(argv[i][j])) // potrei considerare anche il segno +, ma non è richiesto
                return 1;
        }
        // converto to int and push to vector
        const long n = std::atol(argv[i]);
        if (n > std::numeric_limits<int>::max() || n < 0)
            return 1;
        numbers.push_back(n);
    }
    return 0;
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <n1> <n2> ... <nn>" << std::endl;
        return 1;
    }
    std::vector<int> numbers;
    if (parse_args(argc, argv, numbers))
    {
        std::cerr << "Error: invalid arguments" << std::endl;
        return 1;
    }

    PmergeMe x(numbers);

    std::cout << "Before sorting: ";
    x.print();

    // sort numbers vector
    // // sort numbers deque
    // print after sorting
    // print time The indication of the time is deliberately strange in this example.
        // Of course you have to indicate the time used to perform all your
        // operations, both the sorting part and the data management part.
    // print time
}