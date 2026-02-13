/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmory <tmory@student.42antananarivo.mg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 11:34:40 by tmory             #+#    #+#             */
/*   Updated: 2026/02/13 18:34:36 by tmory            ###   ########.fr       */
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

void
PmergeMe::clearChain() {
	(this->_chain).clear();
}

void
PmergeMe::pushBackChain(vec_int &vec) {
	(this->_chain).push_back(vec);
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

vec_int const 
PmergeMe::sortPair() {
	vec_pair			pair = this->getChain();
	vec_pair::iterator	it = pair.begin();
	vec_int				leftOver;

	for (;it != pair.end(); it += 2) {
		if ((it + 1) == pair.end()) {
			leftOver = *it;
			pair.pop_back();
			break; 
		}
		if (*it < *(it + 1))
			std::swap(*it, *(it + 1));
	}
	this->setChain(pair);
	return leftOver;
}

void PmergeMe::makePair() {
	vec_int tmp;
	vec_pair pair = this->getChain();
	vec_pair::iterator it = pair.begin();

	this->clearChain();
	for (; it != pair.end(); it += 2) {
		tmp.insert(tmp.end(), (*it).begin(), (*it).end());
		tmp.insert(tmp.end(), (*(it + 1)).begin(), (*(it + 1)).end());
		this->pushBackChain(tmp);
		tmp.clear();
	}
}

void PmergeMe::fordJohnson() {
	// static size_t	level = 0;
	// size_t			comp = pow(2, level);
	vec_int leftOver;
	
	if (this->getChain().size() <= 1)
		return ;
	leftOver = this->sortPair();
	
	std::cout << "---------------------------" << std::endl;
	std::cout << "pair suite before makePair:" << std::endl;
	PmergeMe::printP<vec_pair, vec_int>(this->getChain());
	if (!leftOver.empty()) {
		std::cout << "left over  = [";
		PmergeMe::printC(leftOver);
	}
	
	this->makePair();
	
	std::cout << "---------------------------" << std::endl;
	std::cout << "pair suite after sort:" << std::endl;
	PmergeMe::printP<vec_pair, vec_int>(this->getChain());
	
	this->fordJohnson();
	
	return ;
}

