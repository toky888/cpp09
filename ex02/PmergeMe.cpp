/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmory <tmory@student.42antananarivo.mg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 11:34:40 by tmory             #+#    #+#             */
/*   Updated: 2026/02/12 01:10:35 by tmory            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {}

void
PmergeMe::setRaw(vec_int input) {
	this->_raw = input;
}

void
PmergeMe::setChain(vec_pair input) {
	this->_chain = input;
}

vec_int
PmergeMe::getRaw() const {
	return this->_raw;
}

vec_pair
PmergeMe::getChain() const {
	return this->_chain;
}

// static void
// sortPairByPair(vec_pair &array) {
// 	vec_pair::iterator it = array.begin();
// 	for (; it != array.end(); ++it) {
// 		if (it->second > it->first)
// 			std::swap(it->second, it->first );
// 	}
// 	std::cout << std::endl;
		
// }

void
PmergeMe::sortPair() {
	vec_pair chain;

	chain = this->getChain();
	vec_pair::const_iterator	it = chain.begin();
	// for (size_t i = 0; it != chain.end(); ++it) {
	// 	if((*it)[0] < (*it)[1] )
	// }
	
}

void PmergeMe::fordJohnson() {
	static size_t	level = 0;
	size_t			comp = pow(2, level);

	
	
	return ;
}

