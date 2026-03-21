/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 15:32:40 by plichota          #+#    #+#             */
/*   Updated: 2026/03/20 19:20:40 by plichota         ###   ########.fr       */
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

class PmergeMe
{
    private:
        std::vector<int> _numbers;
    public:
        PmergeMe();
        PmergeMe(std::vector<int> numbers);
        PmergeMe(const PmergeMe& other);
        PmergeMe& operator=(const PmergeMe& other);
        ~PmergeMe();

        void sortAll(std::vector<int> numbers);
        void print() const;
};

#endif