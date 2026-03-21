/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 15:32:40 by plichota          #+#    #+#             */
/*   Updated: 2026/03/21 18:51:53 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# define GREEN   	"\033[0;32m"
# define YELLOW  	"\033[0;33m"
# define BLUE    	"\033[0;34m"
# define MAGENTA 	"\033[0;35m"
# define RESET   	"\033[0m"

#include <vector>
#include <deque>

class PmergeMe
{
    private:
        std::vector<int> _numbers;
        std::deque<int> _numbersDeque;
    public:
        PmergeMe();
        PmergeMe(std::vector<int> numbers);
        PmergeMe(std::deque<int> numbers);
        PmergeMe(const PmergeMe& other);
        PmergeMe& operator=(const PmergeMe& other);
        ~PmergeMe();

        void sortVector();
        void sortDeque();
        void printVector() const;
        void printDeque() const;
};

#endif