/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmory <tmory@student.42antananarivo.mg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 08:56:24 by tmory             #+#    #+#             */
/*   Updated: 2026/01/19 13:39:53 by tmory            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

Btc::Btc() {
	this->_data.open("data.csv");
	if (!this->_data)
		throw(std::logic_error
			("\"data.csv\" file not found in the current directory."));
	Btc::putIntoMap(this->_data, this->_dataMap);
}

Btc::~Btc() {
}

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
            continue;
        }
        std::stringstream rs(exRateString);

        if (!(rs >> exRate)) {
            continue;
		}
    	dataMap.insert(std::make_pair(date, exRate));
    }
}

mapSD Btc::getDataMap() const {
	return this->_dataMap;
}
