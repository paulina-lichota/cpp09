/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 15:32:38 by plichota          #+#    #+#             */
/*   Updated: 2026/03/20 16:06:35 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>

PmergeMe::PmergeMe() : _numbers() {} // inizializza vettore vuoto

PmergeMe::PmergeMe(std::vector<int> numbers) : _numbers(numbers) {} // inizializza vettore

PmergeMe::PmergeMe(const PmergeMe& other) : _numbers(other._numbers) {} // copia vettore

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
    if (this != &other)
    {
        _numbers = other._numbers;
    }
    return *this;
}

PmergeMe::~PmergeMe() {}

void PmergeMe::print() const
{
    std::vector<int>::const_iterator it = _numbers.begin();
    while (it != _numbers.end())
    {
        std::cout << *it << " ";
        ++it;
    }
}

/*
    Merge-Insertion sort
    minimizza il numero di confronti nel caso peggiore
*/

void PmergeMe::sort()
{
    // sort
}
