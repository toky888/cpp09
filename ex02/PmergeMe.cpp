/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmory <tmory@student.42antananarivo.mg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 11:34:40 by tmory             #+#    #+#             */
/*   Updated: 2026/02/16 19:05:15 by tmory            ###   ########.fr       */
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

static void
testPrintP(std::string const &s, vec_pair const &p, size_t const &level) {
	std::cout << "---------------------------" << std::endl;
	std::cout << s << level << std::endl;
	PmergeMe::printP<vec_pair, vec_int>(p);
}

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

void
PmergeMe::dividePair_indexation(size_t comp) {
	vec_int tmp;
	vec_int tmp2;
	vec_pair pair = this->getChain();
	vec_pair::iterator it = pair.begin();

	this->clearChain();
	for (int i = 0; it != pair.end(); ++it, ++i) {
		tmp.insert(tmp.end(), (*it).begin(), (*it).begin() + comp);
		tmp.push_back(i);
		tmp2.insert(tmp2.end(), (*it).begin() + comp, (*it).end());
		tmp2.push_back(i);
		this->pushBackChain(tmp);
		this->pushBackChain(tmp2);
		tmp.clear();
		tmp2.clear();
	}
}

void
PmergeMe::removeIndex() {
	vec_pair pair = this->getChain();
	vec_pair::iterator it = pair.begin();

	this->clearChain();
	for (; it != pair.end(); ++it) {
		(*it).pop_back();
	}
	this->setChain(pair);
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

void FJInsertion(std::vector<size_t> const jSuit, vec_pair &pair) {
	vec_pair::iterator	index = pair.begin();
	unsigned int		difference;
	vec_pair::iterator insertIt;
	
	difference = 0;
	for (std::vector<size_t>::const_iterator it = jSuit.cbegin();
		it != jSuit.cend(); ++it)
	{
		insertIt = std::lower_bound(pair.begin(), index, *(index + 1));
		pair.insert(insertIt, *(index + 1));
		pair.erase(index + 1);
	}
}

void PmergeMe::fordJohnson() {
	static size_t		level = 0;
	vec_int				leftOver;
	std::vector<size_t>	jSuit;
	vec_pair			pair;
	
	// std::vector<size_t> jacobSthalSuit;
	
	if (this->getChain().size() <= 1)
		return ;
	leftOver = this->sortPair();
	
	// std::cout << "---------------------------" << std::endl;
	// std::cout << "pair suite before makePair:" << std::endl;
	// PmergeMe::printP<vec_pair, vec_int>(this->getChain());
	// if (!leftOver.empty()) {
	// 	std::cout << "left over  = [";
	// 	PmergeMe::printC(leftOver);
	// }
	
	this->makePair();
	
	// testPrintP("pair suite before FJ: level", this->getChain(), level );
	
	++level;
	this->fordJohnson();
	--level;
	size_t			comp = pow(2, level);
	this->dividePair_indexation(comp);
	pair = this->getChain();
	jSuit = PmergeMe::buildJacobsthalOrder(pair.size() / 2);
	FJInsertion(jSuit, pair);
	
	// testPrintP("pair suite after FJ: level", this->getChain(), level );

	this->removeIndex();
	return ;
}

std::vector<size_t>
PmergeMe::buildJacobsthalOrder(size_t n)
{
     std::vector<size_t> order;

	order.push_back(0);
    if (n <= 1)
        return order;

    std::vector<size_t> t;
    t.push_back(1);
    t.push_back(3);

    while (t.back() < n)
        t.push_back(t[t.size()-1] + 2 * t[t.size()-2]);

    // Step 2 — Generate blocks
    size_t prev = 1;  // t0
    for (size_t k = 1; k < t.size(); ++k)
    {
        size_t curr = t[k];
        size_t high = curr < n ? curr : n;

        // Insert indices from high down to prev+1
        for (size_t i = high; i > prev; --i)
            order.push_back(i - 1); // 0-based index

        prev = curr;
        if (curr >= n)
            break;
    }

    return order;
}

