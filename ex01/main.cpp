/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 22:33:41 by plichota          #+#    #+#             */
/*   Updated: 2026/03/11 22:40:00 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>


// You don’t need to handle brackets or decimal numbers.

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <expression>" << std::endl;
        return 1;
    }
    (void) argv;
}

/*
$> ./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
42
$> ./RPN "7 7 * 7 -"
42
$> ./RPN "1 2 * 2 / 2 * 2 4 - +"
0
$> ./RPN "(1 + 1)"
Error
$>
*/