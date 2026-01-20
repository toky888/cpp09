/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmory <tmory@student.42antananarivo.mg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 08:56:24 by tmory             #+#    #+#             */
/*   Updated: 2026/01/20 19:02:08 by tmory            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

Btc::Btc(std::string const &input) {
	this->_data.open("data.csv");
	if (!this->_data)
		throw(std::logic_error
			("\"data.csv\" file not found in the current directory."));
	Btc::putIntoMap(this->_data, this->_dataMap);
	this->_input.open(input.c_str());
	if (!this->_input)
		throw(std::logic_error
			(input + " file not found in the current directory."));
	Btc::putIntoMapInput(this->_input, this->_inputmap);
	this->_data.close();
	this->_input.close();
}

Btc::~Btc() {}

void Btc::putIntoMap(std::ifstream &data, mapSD &dataMap) {
	std::string	header;
	std::string line;
    std::string date;
    std::string exRateString;
    double		exRate;

	std::getline(data, header);
    for (; std::getline(data, line); ) {
        std::stringstream ss(line);

        if (!std::getline(ss, date, ',') ||
            !std::getline(ss, exRateString)) {
            continue ;
        }
        std::stringstream rs(exRateString);

        if (!(rs >> exRate)) {
            continue ;
		}
    	dataMap.insert(std::make_pair(date, exRate));
    }
}

void Btc::putIntoMapInput(std::ifstream &input, mapSD &inputMap) {
	std::string	header;
	std::string	rawLine;
	
	std::getline(input, header);
	Btc::verifyInputHeader(header);
	while (getline(input, rawLine)) {
		Btc::verifyLine(rawLine);
	}
	
	
	
	inputMap.insert(std::make_pair("ads", 77)); // Just to test cause i can t do = void
}

mapSD Btc::getDataMap() const {
	return this->_dataMap;
}

void	Btc::verifyInputHeader(std::string const &head) {
	std::stringstream	headStream(head);
	std::string			date;
	std::string			value;
	
	if ((std::count(head.begin(), head.end(), '|') != 1)) {
		std::cout << "Error: bad header input =>" << head << std::endl;
		return ;
	}
	std::getline(headStream, date, '|');
	std::getline(headStream, value);
	Btc::trim_char(date, ' ');
	Btc::trim_char(value, ' ');

	if (date != "date" || value != "value") {
		std::cout << "Error: bad header input =>" << head << std::endl;
		return ;
	}
	
		
	// std::cout << "THI IS A TEST " 
	// 	<< date << "|" << value  << std::endl;
	
}

void	Btc::trim_char(std::string& s, char c)
{
    while (!s.empty() && s[0] == c)
        s.erase(0, 1);

    while (!s.empty() && s[s.size() - 1] == c)
        s.erase(s.size() - 1, 1);
}

void	Btc::verifyLine(std::string const &line) {
	std::stringstream	rawLine(line);
	std::string			date;
	std::string			value;
	
	if ((std::count(line.begin(), line.end(), '|') != 1)) {
		std::cout << "Error: bad header input =>" << line << std::endl;
		return ;
	}
	std::getline(rawLine, date, '|');
	std::getline(rawLine, value);
	Btc::trim_char(date, ' ');
	Btc::trim_char(value, ' ');
}
