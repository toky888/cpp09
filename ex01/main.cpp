/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmory <tmory@student.42antananarivo.mg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 15:17:11 by tmory             #+#    #+#             */
/*   Updated: 2026/01/26 16:29:18 by tmory            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

bool
validchar(std::string const &av) {
	size_t		firstPos;
	std::string	allowedChar;

	allowedChar = "0123456789+-/* \t";
	firstPos = av.find_first_not_of(allowedChar);
	return firstPos == std::string::npos;
}

bool
isSpaceBetween(std::string const &av) {
	std::string::const_iterator it = av.begin();
	for (; it != av.end(); ++it) {
		if (*it != ' ' && *it != '\t') {
			if (++it == av.end())
				break;
			if (*it != ' ' && *it != '\t')
				return false;
		}
	}
	return true;
}

void
checkError(std::string av) {
	// std::cout <<  av  << std::endl;
	if(!validchar(av))
		throw (std::runtime_error("\033[31mError\033[0m"));
	if (!isSpaceBetween(av))
		throw (std::runtime_error("\033[31mError\033[0m: need space between operands and operators. Operands < 10"));
}

int	main(int ac, char **av) {
	try {
		if (ac != 2)
			throw (std::runtime_error("\033[31mError:\033[0m use => ./RPN \"[arguments]\""));
		checkError(av[1]);
		RPN rpn(av[1]);
		
		rpn.calculRPN();
		std::cout << rpn.getResult() << std::endl;
	}
	catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
	
	return 0;
}
