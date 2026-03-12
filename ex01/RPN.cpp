/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 22:35:08 by plichota          #+#    #+#             */
/*   Updated: 2026/03/12 17:30:09 by plichota         ###   ########.fr       */
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

// int RPN::parse_and_fill_stack(std::string s)
// {
//     // has to contain only digits or operators or spaces
//     for (std::string::iterator it = s.begin(); it != s.end(); ++it)
//     {
//         if (!isValid(*it)) {
//             std::cerr << "Error" << std::endl;
//             return 1;
//         }
//     }

//     // insert characters in stack IN REVERSE (LIFO)
//     for (size_t i = s.size(); i > 0; i--)
//     {
//         if (s[i - 1] != ' ')
//             stack.push(s[i - 1]);
//     }
//     return 0;
// }

static int apply_operator(int a, int b, char op)
{
    std::cout << YELLOW << "apply operator: " << a << " " << op << " " << b << RESET << std::endl;
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

// void RPN::compute()
// {
//     bool first = true;
//     int result = 0;

//     while (stack.size() >= 2) // non ripusho il result, tengo come int a parte
//     {
//         if (first)
//         {
//             std::cout << "is first, so pop : " << stack.top() << std::endl;
//             char c1 = stack.top(); // prendo elemento
//             stack.pop(); // elimino elemento
//             if (!std::isdigit(c1))
//             {
//                 std::cerr << "Error: Not a number" << std::endl;
//                 return ;
//             }
//             result = c1 - '0';
//             first = false;
//         }

//         std::cout << "pop second number : " << stack.top() << std::endl;
//         char c2 = stack.top(); // prendo elemento
//         stack.pop(); // elimino elemento
//         if (!std::isdigit(c2))
//         {
//             std::cerr << "Error: Not enough operands" << std::endl;
//             return ;
//         }
//         int n2 = c2 - '0';

//         std::cout << "pop operator : " << stack.top() << std::endl;
//         char op = stack.top(); // prendo operatore
//         stack.pop(); // elimino elemento
//         if (!isOperator(op))
//         {
//             std::cerr << "Error: Not an operator" << std::endl;
//             return ;
//         }
//         // apply operator
//         std::cout << "apply operator " << op << " on " << result << " and " << n2 << std::endl;
//         result = apply_operator(result, n2, op);
//         std::cout << "result : " << result << std::endl;
//         if (result == INT_MAX)
//         {
//             std::cerr << "Error: Invalid operator" << std::endl;
//             return ;
//         }
//     }
//     if (stack.size() != 0)
//     {
//         std::cerr << "Error" << std::endl;
//         std::cout << "Remaining elements in stack : " << std::endl;
//         print_LIFO();
//     }
//     std::cout << result << std::endl;
// }

static int isValidString(const std::string& s)
{
    for (std::string::const_iterator it = s.begin(); it != s.end(); ++it)
    {
        if (!isValid(*it)) {
            std::cerr << "Error" << std::endl;
            return 0;
        }
    }
    return 1;
}

void RPN::compute(std::string s)
{
    std::stack<int> temp;

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
            temp.push(s[i] - '0');
            // stack.push(s[i]);
        }
        else if (isOperator(s[i]))
        {
            if (temp.size() < 2)
            {
                std::cerr << "Error: Not enough operands" << std::endl;
                return ;
            }
            int b = temp.top();
            temp.pop();
            int a = temp.top();
            temp.pop();
            int result = apply_operator(a, b, s[i]);
            if (result == INT_MAX)
            {
                std::cerr << "Error: Invalid operator" << std::endl;
                return ;
            }
            temp.push(result);
        }
    }
    if (temp.size() != 1)
    {
        std::cerr << "Error" << std::endl;
        std::cout << "Remaining elements in stack : " << std::endl;
        print_LIFO();
        return ;
    }
    std::cout << temp.top() << std::endl;
}

void RPN::print_LIFO()
{
    std::stack<char> temp = stack;
    while (!temp.empty())
    {
        std::cout << temp.top() << " ";
        temp.pop();
    }
    std::cout << std::endl;
}