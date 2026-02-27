/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmory <tmory@student.42antananarivo.mg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 09:02:19 by tmory             #+#    #+#             */
/*   Updated: 2026/02/24 08:50:13 by tmory            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (std::cout << "Error: invalid argument number" << std::endl, 1);
	try {
		Btc	data(argv[1]);
	}
	catch (std::exception &e) {
		std::cout << "Error : " << e.what() << std::endl;
	}
	return 0;
}
