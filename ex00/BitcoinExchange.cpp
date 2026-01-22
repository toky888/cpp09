/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmory <tmory@student.42antananarivo.mg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 08:56:24 by tmory             #+#    #+#             */
/*   Updated: 2026/01/22 15:51:35 by tmory            ###   ########.fr       */
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
	Btc::putIntoMapInput(this->_input, this->_inputMap);
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
		Btc::verifyLineNPrint(rawLine, inputMap);
	}
	 // Just to test cause i can t do = void
}

mapSD Btc::getDataMap() const {
	return this->_dataMap;
}

mapSD Btc::getInputMap() const {
	return this->_inputMap;
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
}

void	Btc::trim_char(std::string& s, char c)
{
    while (!s.empty() && s[0] == c)
        s.erase(0, 1);
    while (!s.empty() && s[s.size() - 1] == c)
        s.erase(s.size() - 1, 1);
}

bool Btc::isDouble(std::string const &s) {
	char *		end;
	int			check;
	std::string	str;
	
	if (s.empty())
		return false;
	end = NULL;
	str = s;
	check = 0;
	std::strtod(str.c_str(), &end);
	return (check == 0 && end == str.c_str() + str.size()); 
}

static void	trim_charBefore(std::string& s, char c)
{
    while (!s.empty() && s[0] == c)
        s.erase(0, 1);
}

static bool	cleanCheckValue(std::string &value) {
	int			lengthExtractSafe;
	std::string	value1000;
	
	trim_charBefore(value, '+');
	trim_charBefore(value, '0');
	lengthExtractSafe = std::min(4, static_cast<int>(value.length()));
	value1000 = value.substr(0, lengthExtractSafe);
	std::stringstream	val1000(value1000);
	val1000 >> lengthExtractSafe;
	if (lengthExtractSafe > 1000)
		return true;
	return false;
}

static bool	cleanCheckDate(std::string &date) {
	std::tm tm = {};
	std::tm original = {};
	char*	end;
	
	end = NULL;
	Btc::trim_char(date, ' ');
	Btc::trim_char(date, '\t');
	end = strptime(date.c_str(), "%Y-%m-%d", &tm);
	original = tm;
	if (!end || *end != '\0')
		return false;
	if (mktime(&tm) == -1)
		return false;
	tm.tm_isdst = -1;
	if (tm.tm_year != original.tm_year
		|| tm.tm_mon != original.tm_mon
		|| tm.tm_mday !=  original.tm_mday)
		return false;
	return true;
}

static void	cleanRawLine(std::stringstream	&rawLine, std::string &date, std::string &value) {
	std::getline(rawLine, date, '|');
	std::getline(rawLine, value);
	Btc::trim_char(date, ' ');
	Btc::trim_char(value, ' ');
}

e_error	Btc::checkLineForSwitchNPrint(std::string const &line, mapSD &inputMap) {
	
	std::stringstream	rawLine(line);
	std::string			date;
	std::string			value;
	double				valuedd;
	
	if ((std::count(line.begin(), line.end(), '|') != 1))
		return BAD_INPUT;
	cleanRawLine(rawLine, date, value);
	if (!cleanCheckDate(date))
		return BAD_INPUT;
	if (!Btc::isDouble(value))
		return NOT_NUM;
	if (value[0] == '-')
		return NEGATIVE_NUM;
	if (cleanCheckValue(value))
		return TOO_HIGH_NUM;
	std::stringstream	valued(value);
	
	valued >> valuedd;
	inputMap.insert(std::make_pair(date, valuedd));
	return OK;
}

void	Btc::verifyLineNPrint(std::string const &line, mapSD &inputMap) {
	switch (checkLineForSwitchNPrint(line, inputMap)) {
		case BAD_INPUT:
			std::cout << "Error: bad input =>" << line << std::endl;
			break;
		case NOT_NUM:
			std::cout << "Error: bad input =>" << line << std::endl;
			break;
		case NEGATIVE_NUM:
			std::cout << "Error: not a positive number." << std::endl;
			break;
		case TOO_HIGH_NUM:
			std::cout << "Error: too large a number." << std::endl;
			break;
		default:
			
			break;
	}
}
