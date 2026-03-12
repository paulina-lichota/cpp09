/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 22:35:08 by plichota          #+#    #+#             */
/*   Updated: 2026/03/12 15:44:59 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <algorithm> // all_of
#include <stdexcept> // std::runtime_error
#include <cctype> // isdigit
#include <climits> // INT_MAX

RPN::RPN()
{
}

RPN::RPN(std::string s)
{
    if (parse_and_fill_stack(s) != 0)
        throw std::runtime_error("Invalid input for RPN constructor");
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

static int isValid(char c)
{
    return std::isdigit(c) || c == '+' || c == '-' || c == '*' || c == '/' || std::isspace(c);
}

static int isOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

/*
    LAMBDA EXPRESSION (C++11)
    function that takes parameters and returns a value, without having to name the function
    [capture](parameters) -> return_type { body }

    es.
    instead of writing isValid we can write
    auto isValid = [](char c) { return std::isdigit(c) || c == '+' || c == '-' || c == '*' || c == '/' || std::isspace(c); };
*/

/*
    CHECK IF ALL ELEMENTS SATISFY A CONDITION (C++11)
    std::all_of(s.begin(), s.end(), foo)
*/

int RPN::parse_and_fill_stack(std::string s)
{
    // has to contain only digits or operators or spaces
    for (std::string::iterator it = s.begin(); it != s.end(); ++it)
    {
        // std::cout << "char: " << *it << std::endl;
        if (!isValid(*it)) {
            std::cerr << "Error" << std::endl;
            return 1;
        }
    }

    // insert characters in stack
    for (size_t i = 0; i < s.size(); i++)
    {
        if (s[i] != ' ')
            stack.push(s[i]);
    }
    return 0;
}

static int apply_operator(int a, int b, char op)
{
    if (op == '+')
        return a + b;
    else if (op == '-')
        return a - b;
    else if (op == '*')
        return a * b;
    else if (op == '/')
        return a / b;
    return INT_MAX; // should never happen
}

void RPN::compute()
{
    bool first = true;
    int result = 0;

    while (stack.size() >= 2) // non ripusho il result, tengo come int a parte
    {
        if (first)
        {
            char c1 = stack.top(); // prendo elemento
            stack.pop(); // elimino elemento
            if (!std::isdigit(c1))
            {
                std::cerr << "Error: Not a number" << std::endl;
                return ;
            }
            result = atoi(&c1);
        }

        char c2 = stack.top(); // prendo elemento
        stack.pop(); // elimino elemento
        if (!std::isdigit(c2))
        {
            std::cerr << "Error: Not enough operands" << std::endl;
            return ;
        }
        int n2 = atoi(&c2);

        char op = stack.top(); // prendo operatore
        stack.pop(); // elimino elemento
        if (!isOperator(op))
        {
            std::cerr << "Error: Not an operator" << std::endl;
            return ;
        }
        // apply operator
        result = apply_operator(result, n2, op);
        if (result == INT_MAX)
        {
            std::cerr << "Error: Invalid operator" << std::endl;
            return ;
        }
    }
    if (stack.size() != 1)
        std::cerr << "Error" << std::endl;
    std::cout << stack.top() << std::endl;
}