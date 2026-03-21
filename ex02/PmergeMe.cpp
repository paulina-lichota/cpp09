/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 15:32:38 by plichota          #+#    #+#             */
/*   Updated: 2026/03/21 22:00:20 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>

PmergeMe::PmergeMe() : _numbers(), _numbersDeque() {} // inizializza vettore vuoto

void PmergeMe::init_deque(const std::deque<int>& input) {
    _numbersDeque = input;
}

void PmergeMe::init_vector(const std::vector<int>& input) {
    _numbers = input;
}

PmergeMe::PmergeMe(const PmergeMe& other) : _numbers(other._numbers), _numbersDeque(other._numbersDeque) {} // copia vettore e deque

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
    if (this != &other)
    {
        _numbers = other._numbers;
        _numbersDeque = other._numbersDeque;
    }
    return *this;
}

PmergeMe::~PmergeMe() {}

void PmergeMe::printVector() const
{
    std::vector<int>::const_iterator it = _numbers.begin();
    while (it != _numbers.end())
    {
        std::cout << YELLOW << *it << " ";
        ++it;
    }
    std::cout << RESET << std::endl;
}

void PmergeMe::printDeque() const
{
    std::deque<int>::const_iterator it = _numbersDeque.begin();
    while (it != _numbersDeque.end())
    {
        std::cout << YELLOW << *it << " ";
        ++it;
    }
    std::cout << RESET << std::endl;
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
    if (major.size() > 1) // evito una chiamata
        major = sort(major);

    // inserisco i numeri di minor in major con binary search (lower_bound usa binary search)
    for (size_t i = 0; i < minor.size(); i++)
    {
        // lower_bound restituisce un iteratore al primo elemento maggiore o uguale a minor[i]
        std::vector<int>::iterator it = std::lower_bound(major.begin(), major.end(), minor[i]);
        // inserisce prima dell’elemento puntato da it
        major.insert(it, minor[i]);
    }

    // inserisco stray (se c'è)
    if (stray != -1)
    {
        std::vector<int>::iterator it = std::lower_bound(major.begin(), major.end(), stray);
        major.insert(it, stray);
    }

    return major;
}

void PmergeMe::sortVector()
{
    _numbers = sort(_numbers);
}

/* Subject: 
    It is strongly advised to implement your algorithm for each container
    and thus to avoid using a generic function.
*/

static std::deque<int> sort2(std::deque<int> numbers) // local copy
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

    std::deque<int> major;
    std::deque<int> minor;

    // qui dovrei usare iterator perche' deque e' piu' lento con operatore [] rispetto a vector
    // ma il subject non e' chiaro... uso comunque [] per vedere la differnza di prestazioni tra vector e deque
    // lo scopo sarebbe evitare i template
    for (size_t i = 0; i < numbers.size(); i += 2)
    {
        if (numbers[i] < numbers[i + 1])
            std::swap(numbers[i], numbers[i + 1]);
        major.push_back(numbers[i]);
        minor.push_back(numbers[i + 1]);
    }

    // a questo punto tengo da parte minor
    // sorto major che fara' da scheletro ordinato
    if (major.size() > 1) // evito una chiamata
        major = sort2(major);

    // inserisco i numeri di minor in major con binary search (lower_bound usa binary search)
    for (size_t i = 0; i < minor.size(); i++)
    {
        // lower_bound restituisce un iteratore al primo elemento maggiore o uguale a minor[i]
        std::deque<int>::iterator it = std::lower_bound(major.begin(), major.end(), minor[i]);
        // inserisce prima dell’elemento puntato da it
        major.insert(it, minor[i]);
    }

    // inserisco stray (se c'è)
    if (stray != -1)
    {
        std::deque<int>::iterator it = std::lower_bound(major.begin(), major.end(), stray);
        major.insert(it, stray);
    }

    return major;
}

void PmergeMe::sortDeque()
{
    _numbersDeque = sort2(_numbersDeque);
}

int PmergeMe::getVectorSize() const
{
    return _numbers.size();
}

int PmergeMe::getDequeSize() const
{
    return _numbersDeque.size();
}
