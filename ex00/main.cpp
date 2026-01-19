/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmory <tmory@student.42antananarivo.mg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 09:02:19 by tmory             #+#    #+#             */
/*   Updated: 2026/01/19 14:01:04 by tmory            ###   ########.fr       */
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

// int	main(int argv, std::string *argc)
int	main()
{
	// if (argv != 2)
	// 	return (1, std::cout << "Error: invalid argument number" << std::endl);
	try {
		Btc	data;
		printMap(data.getDataMap());
	}
	catch (std::exception &e) {
		std::cout << "Error : " << e.what() << std::endl;
	}
	return 0;
}
