/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 14:19:01 by plichota          #+#    #+#             */
/*   Updated: 2026/03/21 19:14:26 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

#include <string>
#include <iostream>
#include <vector>
#include <cstring> // strlen
#include <cstdlib> // atoi
#include <limits> // numeric_limits
#include <ctime> // clock, CLOCKS_PER_SEC
#include <iomanip> // setw

// Subject: "The management of errors related to duplicates is left to your discretion."

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

    PmergeMe x;
    clock_t start = clock();
    x.init_vector(numbers);
    std::cout << "Before sorting: ";
    x.printVector();
    x.sortVector();
    clock_t end = clock();
    std::cout << "After sorting: ";
    x.printVector();
    double t = (double)(end - start) / CLOCKS_PER_SEC;
    std::cout << "Time to process a range of " << std::setw(4) << x.getVectorSize() 
        << " elements with std::vector : " << t << " us" << std::endl;
}