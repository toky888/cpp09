/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmory <tmory@student.42antananarivo.mg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 11:34:40 by tmory             #+#    #+#             */
/*   Updated: 2026/02/05 11:59:37 by tmory            ###   ########.fr       */
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

vec_int PmergeMe::generateIndex(size_t size) {
	vec_int index;

	for (int i = 0; static_cast<size_t> (i) < size; ++i) {
		index.push_back(i);
	}
	return index;
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

// TEST FOR PRINT
static int
printPairTest(t_pair const &pair) {
	size_t i;
	static int level = 0;
	std::cout << "level " <<  level << std::endl;
	for (i = 0; i != pair.bigPair.size(); i++) {
		std::cout << pair.bigPair[i] << ":" << pair.smallPair[i] << std::endl;
	}
	std::cout << pair.leftOver << std::endl;
	level++;
	return level;
}

// static void
// insertion(vec_int &bigPair, vec_int const &smallPair){
	
// }

void PmergeMe::fordJohnson(vec_int &chain, vec_int index) {
	t_pair	pairs;
	vec_int	newchain;
	vec_int	oldBigPair;
	vec_int	indexOP;

	static int level = 0;// TEST


	pairs.leftOver =  NO_LEFTOVER;
	if (chain.size() <= 1)
		return ;
	sortPair(pairs, chain);
	

	level = printPairTest(pairs) - 1;// TEST
	
	oldBigPair = pairs.bigPair;
	indexOP = PmergeMe::generateIndex(oldBigPair.size());
	std::cout << "----------------" << std::endl;
	PmergeMe::fordJohnson(pairs.bigPair, indexOP);
	

	std::cout << "level " << level  << std::endl;
	
	newchain = pairs.bigPair;
	std::cout << "\033[91mpairs.bigPair chain :\033[0m";// TEST
	PmergeMe::printC(newchain);
	
	vec_int::iterator it = std::lower_bound(newchain.begin(),
	newchain.end(), pairs.smallPair[0]); // now change the "newchain.end()" to the index of index[0] of smallPair
	if (it == newchain.end())
	std::cout << "NOOOOOOOOOOO" << std::endl;
	std::cout << "it of lower_bound = " <<  *it  << " for " << pairs.smallPair[0]<< std::endl;
	newchain.insert(it, pairs.smallPair[0]);
	
	// newchain.lower_;

	
	std::cout << "\033[32mnew chain in level : \033[0m";// TEST
	--level;// TEST
	PmergeMe::printC(newchain);
	chain = newchain;
	
	// insertion(pairs.bigPair, pairs.smallPair);
	return ;
}

