/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmory <tmory@student.42antananarivo.mg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 09:02:19 by tmory             #+#    #+#             */
/*   Updated: 2026/01/20 16:58:38 by tmory            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
template <typename T>
void printMap(T map){
	typename T::iterator it = map.begin();
	for (; it != map.end(); ++it)
	{
		std::cout << it->first <<","<< it->second  << std::endl;
	}
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (std::cout << "Error: invalid argument number" << std::endl, 1);
	try {
		Btc	data(argv[1]);
		// printMap(data.getDataMap());
	}
	catch (std::exception &e) {
		std::cout << "Error : " << e.what() << std::endl;
	}
	return 0;
}
