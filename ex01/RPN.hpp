/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 22:34:07 by plichota          #+#    #+#             */
/*   Updated: 2026/03/12 18:23:13 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# define GREEN   	"\033[0;32m"
# define YELLOW  	"\033[0;33m"
# define BLUE    	"\033[0;34m"
# define MAGENTA 	"\033[0;35m"
# define RESET   	"\033[0m"

#include <stack>
#include <string>
#include <iostream>

/*
    REVERSE POLISH NOTATION
    Read left to right.
    Push numbers onto a stack.
    When an operator appears, pop the last two numbers, apply the operator, and push the result back.
*/
class RPN
{
    private:
        std::stack<int> _stack;
    public:
        RPN();
        RPN(const RPN& other);
        RPN& operator=(const RPN& other);
        ~RPN();
        void compute(std::string s);
        void print_LIFO();
};

#endif