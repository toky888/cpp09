/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmory <tmory@student.42antananarivo.mg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 08:56:20 by tmory             #+#    #+#             */
/*   Updated: 2026/01/22 15:51:13 by tmory            ###   ########.fr       */
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
# include <ctime>
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
	mapSD			_inputMap;
	std::string		_dateInput;
	double			_valueImput;
	Btc(Btc const &src);
	Btc &operator=(Btc const &rhs);
	Btc();
public:
	Btc(std::string const &input);
	~Btc();
	
	mapSD			getDataMap() const;
	mapSD			getInputMap() const;
	static void		putIntoMap(std::ifstream &data, mapSD &dataMap);
	static void		putIntoMapInput(std::ifstream &input, mapSD &inputMap);
	static void		verifyInputHeader(std::string const & head);
	static void		trim_char(std::string& s, char c);
	static bool		isDouble(std::string const &s);
	static e_error	checkLineForSwitchNPrint(std::string const &line, mapSD &inputMap);
	static void		verifyLineNPrint(std::string const &line, mapSD &inputMap);
};

#endif
