/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmory <tmory@student.42antananarivo.mg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 11:34:40 by tmory             #+#    #+#             */
/*   Updated: 2026/02/04 13:22:28 by tmory            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {}

void PmergeMe::setInput(vec_int input) {
	this->_input = input;
}

vec_int
PmergeMe::getPair() const {
	return this->_input;
}

static	void
sortPair(t_pair &pairs, vec_int &array) {
	vec_int::iterator	it = array.begin();
	
	for(; it != array.end(); it += 2) {
		if (it + 1 == array.end()) {
			pairs.leftOver = *it;
			break;
		}
		if (*it < *(it + 1)) {
			pairs.bigPair.push_back(*(it + 1));
			pairs.smallPair.push_back(*it);
		}
		else {
			pairs.smallPair.push_back(*(it + 1));
			pairs.bigPair.push_back(*it);
		}
	}
}

static void printPairTest(t_pair const &pair) {
	size_t i;
	static int level = 0;
	std::cout << "level " <<  level << std::endl;
	for (i = 0; i != pair.bigPair.size(); i++) {
		std::cout << pair.bigPair[i] << ":" << pair.smallPair[i] << std::endl;
	}
	std::cout << pair.leftOver << std::endl;
	level++;
	
}

void PmergeMe::fordJohnson(vec_int &bigPair) {
	t_pair	pairs;
	
	pairs.leftOver =  NO_LEFTOVER;
	if (bigPair.size() <= 1)
		return ;
	sortPair(pairs, bigPair);
	
	printPairTest(pairs);
	std::cout << "----------------" << std::endl;
	PmergeMe::fordJohnson(pairs.bigPair);
	return ;
}

