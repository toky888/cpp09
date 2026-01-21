/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmory <tmory@student.42antananarivo.mg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 08:56:20 by tmory             #+#    #+#             */
/*   Updated: 2026/01/21 16:50:49 by tmory            ###   ########.fr       */
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
# include <algorithm> 
# include <cstdlib>
typedef std::map<std::string, double>	mapSD;
enum e_error {
	OK,
	BAD_INPUT,
	NOT_NUM,
	NEGATIVE_NUM,
	TOO_HIGH_NUM
};

class Btc{
private:
	std::ifstream	_data;
	std::ifstream	_input;
	mapSD			_dataMap;
	mapSD			_inputmap;
	Btc(Btc const &src);
	Btc &operator=(Btc const &rhs);
	Btc();
public:
	Btc(std::string const &input);
	~Btc();
	
	mapSD			getDataMap() const;
	static void		putIntoMap(std::ifstream &data, mapSD &dataMap);
	static void		putIntoMapInput(std::ifstream &input, mapSD &inputMap);
	static void		verifyInputHeader(std::string const & head);
	static void		trim_char(std::string& s, char c);
	static bool		isDouble(std::string const &s);
	static e_error	checkLineForSwitch(std::string const &line);
	static void		verifyLine(std::string const &line);
};

#endif
