/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmory <tmory@student.42antananarivo.mg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 08:56:20 by tmory             #+#    #+#             */
/*   Updated: 2026/01/19 13:39:07 by tmory            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP
# include <map>
# include <iomanip>
# include <cmath>
# include <string>
# include <iostream>
# include <fstream>
# include <sstream>
typedef std::map<std::string, double>	mapSD;

class Btc{
private:
	std::ifstream	_data;
	mapSD			_dataMap;
	Btc(Btc const &src);
	Btc &operator=(Btc const &rhs);
public:
	Btc();
	~Btc();
	
	static void		putIntoMap(std::ifstream &data, mapSD &dataMap);
	mapSD			getDataMap() const;
	std::ifstream	getData() const;
};

#endif
