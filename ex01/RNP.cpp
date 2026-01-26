/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RNP.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmory <tmory@student.42antananarivo.mg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 15:18:58 by tmory             #+#    #+#             */
/*   Updated: 2026/01/26 16:20:58 by tmory            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RNP.hpp"

static void
trim_char(std::string& s, char c)
{
    while (!s.empty() && s[0] == c)
        s.erase(0, 1);
    while (!s.empty() && s[s.size() - 1] == c)
        s.erase(s.size() - 1, 1);
}

RNP::RNP(std::string input) : _result(0) {
	trim_char(input, ' ');
	trim_char(input, '\t');
	this->_input << input;
}

RNP::~RNP() {}


static void
addStack(std::string const &opr, std::stack<double> &pile) {
	double				num;
	std::stringstream	ss;

	ss << opr;
	ss >> num;
	pile.push(num);
}

static void
twoLastOperandOperation(std::stack<double> &pile, char op) {
	double opd1;
	double opd2;

	opd2 = pile.top();
	pile.pop();
	opd1 = pile.top();
	pile.pop();
	switch (op) {
	case '+':
		pile.push(opd1 + opd2);
		break;
	case '-':
		pile.push(opd1 - opd2);
		break;
	case '*':
		pile.push(opd1 * opd2);
		break;
	case '/':
		pile.push(opd1 / opd2);
		break;
	default:
		break;
	}
}

void
RNP::calculRNP() {
	std::string	opr;
	std::string	operators;
	
	while (getline(this->_input, opr, ' ')) {
		std::cout << opr  << std::endl;
		
		if (std::isdigit(opr[0]))
			addStack(opr, this->_pile);
		else {
			if (this->_pile.empty() || this->_pile.size() == 1)
				throw (std::runtime_error("Error XX"));
			twoLastOperandOperation(this->_pile, opr[0]);
		}
	}
	//verify if _pile.size() != 1
	if (this->_pile.size() != 1)
		throw (std::runtime_error("ErrorYY"));
	this->_result = this->_pile.top();
}

double
RNP::getResult() const {
	return this->_result;
}
