/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 22:35:08 by plichota          #+#    #+#             */
/*   Updated: 2026/03/12 18:24:25 by plichota         ###   ########.fr       */
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

RPN::RPN(const RPN& other) : _stack(other._stack)
{
}

RPN& RPN::operator=(const RPN& other)
{
    if (this != &other)
        _stack = other._stack;
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

static int apply_operator(int a, int b, char op)
{
    // std::cout << YELLOW << "apply operator: " << a << " " << op << " " << b << RESET << std::endl;
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

static int isValidString(const std::string& s)
{
    for (std::string::const_iterator it = s.begin(); it != s.end(); ++it)
    {
        if (!isValid(*it)) {
            return 0;
        }
    }
    return 1;
}

void RPN::compute(std::string s)
{
    while (!_stack.empty()) {
        _stack.pop();
    }

    // has to contain only digits or operators or spaces
    if (!isValidString(s)) {
        std::cerr << "Error" << std::endl;
        return ;
    }

    // insert characters in stack IN REVERSE (LIFO)
    for (size_t i = 0; i < s.length(); i++)
    {
        if (std::isdigit(s[i]))
        {
            // convert char to int and push in temp stack
            _stack.push(s[i] - '0');
        }
        else if (isOperator(s[i]))
        {
            if (_stack.size() < 2)
            {
                std::cerr << "Error: Not enough operands" << std::endl;
                return ;
            }
            int b = _stack.top();
            _stack.pop();
            int a = _stack.top();
            _stack.pop();
            int result = apply_operator(a, b, s[i]);
            if (result == INT_MAX)
            {
                std::cerr << "Error: Invalid operator" << std::endl;
                return ;
            }
            _stack.push(result);
        }
    }
    if (_stack.size() != 1)
    {
        std::cerr << "Error" << std::endl;
        // std::cout << "Remaining elements in stack : " << std::endl;
        // print_LIFO();
        return ;
    }
    std::cout << _stack.top() << std::endl;
}

void RPN::print_LIFO()
{
    std::stack<int> temp = _stack;
    while (!temp.empty())
    {
        std::cout << temp.top() << " ";
        temp.pop();
    }
    std::cout << std::endl;
}