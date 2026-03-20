/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 15:32:38 by plichota          #+#    #+#             */
/*   Updated: 2026/03/20 19:02:04 by plichota         ###   ########.fr       */
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
    std::cout << std::endl;
}

/*
    Merge-Insertion sort
    minimizza il numero di confronti nel caso peggiore
*/

static std::vector<int> sort(std::vector<int> numbers) // local copy
{
    // caso base
    if (numbers.size() <= 1)
        return numbers;

    // gestisco stray (elemento senza coppia)
    // lo parcheggio come il set di numeri piccoli
    // lo inseriro' alla fine con binary search insieme ai numeri piccoli
    int stray = -1;
    if (numbers.size() % 2 != 0)
    {
        stray = numbers.back();
        numbers.pop_back();
    }

    std::vector<int> major;
    std::vector<int> minor;
    
    std::cout << "debug: length " << numbers.size() << std::endl;
    
    // secondo l'algoritmo le coppie devono essere ordinate in modo decrescente
    //  cosi' prendo il primo elemento e inserisco in major
    // ! condensato in un singolo step (avrei potuto usare pair)
    for (size_t i = 0; i < numbers.size(); i += 2)
    {
        if (numbers[i] < numbers[i + 1])
            std::swap(numbers[i], numbers[i + 1]);
        major.push_back(numbers[i]);
        minor.push_back(numbers[i + 1]);
    }

    // a questo punto tengo da parte minor
    // sorto major che fara' da scheletro ordinato
    major = sort(major);

    // faccio binary search per inserire i piu' piccoli e lo stray (se c'è)
    for (size_t i = 0; i < minor.size(); i++)
    {
        /* inserisco in major con binary search */
        std::vector<int>::iterator it = std::lower_bound(major.begin(), major.end(), stray);
        major.insert(it, stray);
    }

    // inserisco stray (se c'è)
    if (stray != -1)
    {
        std::vector<int>::iterator it = std::lower_bound(major.begin(), major.end(), stray);
        major.insert(it, stray);
    }

    return major;
}

void PmergeMe::sortAll(std::vector<int> numbers)
{
    _numbers = sort(numbers);
}

