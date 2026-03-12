/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 22:35:08 by plichota          #+#    #+#             */
/*   Updated: 2026/03/12 14:32:15 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <algorithm> // all_of
#include <cctype> // isdigit

RPN::RPN()
{
}

RPN::RPN(std::string s)
{
    parse_and_fill_stack(s);
}

RPN::RPN(const RPN& other) : stack(other.stack)
{
}

RPN& RPN::operator=(const RPN& other)
{
    if (this != &other)
        stack = other.stack;
    return *this;
}

RPN::~RPN()
{
}

/*
    LAMBDA EXPRESSION (C++11)
    function that takes parameters and returns a value, without having to name the function
    [capture](parameters) -> return_type { body }

    es.
    instead of writing isValid we can write
    auto isValid = [](char c) { return std::isdigit(c) || c == '+' || c == '-' || c == '*' || c == '/' || std::isspace(c); };
*/

int isValid(char c)
{
    return std::isdigit(c) || c == '+' || c == '-' || c == '*' || c == '/' || std::isspace(c);
}

int RPN::parse_and_fill_stack(std::string s)
{
    // has to contain only digits or operators or spaces
    if (!std::all_of(s.begin(), s.end(), isValid))
    {
        std::cerr << "Error: Invalid character in expression" << std::endl;
        return 1;
    }

    // insert characters in stack
    return 0;
}