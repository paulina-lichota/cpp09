/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 22:34:07 by plichota          #+#    #+#             */
/*   Updated: 2026/03/12 14:31:38 by plichota         ###   ########.fr       */
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

class RPN
{
    private:
        std::stack<int> stack;
        int parse_and_fill_stack(std::string s); // devo accedere a stack quindi non puo' essere static
    public:
        RPN();
        RPN(std::string s);
        RPN(const RPN& other);
        RPN& operator=(const RPN& other);
        ~RPN();
};

#endif