/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmory <tmory@student.42antananarivo.mg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 11:34:40 by tmory             #+#    #+#             */
/*   Updated: 2026/02/18 01:13:01 by tmory            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {}

void
PmergeMe::setRaw(vec_int input) {
	this->_rawVec = input;
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
	return this->_rawVec;
}

vec_pair
PmergeMe::getChain() const {
	return this->_chain;
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

void
PmergeMe::makePair() {
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

void
PmergeMe::cleanData() {
	vec_pair	chain;
	vec_int		raw;

	chain = this->getChain();
	for (vec_pair::iterator it = chain.begin(); it != chain.end(); ++it) {
		raw.push_back(*(it->begin()));
	}
	this->setRaw(raw);
}

static void
newMainChain(vec_pair &v, vec_pair const &pair) {
	PmergeMe	tmp;
	int i;
	vec_pair	p;
	vec_int		tmpV;

	tmp.setChain(pair);
	tmp.removeIndex();
	p = tmp.getChain();
	i = 0;
	for (vec_pair::const_iterator	it = p.begin(); it != p.end(); it += 2)
	{
		if (it + 1 == p.end()) {
			std::cout << "Problem"  << std::endl;
			break;
		}
		tmpV = *it;
		tmpV.push_back(i);
		v.push_back(tmpV);
		tmpV.clear();
		++i;
	}
}

static void
LOinsertion(vec_pair &pair, vec_int &lo) {
	vec_pair::iterator it = std::lower_bound(pair.begin(), pair.end(), lo);
	lo.push_back(-42);
	pair.insert(it, lo);
}

static void
FJInsertionLoop(std::vector<size_t> const &jSuit, vec_pair &mainChain, vec_pair::iterator const	&index) {
	size_t				diff = 0;
	size_t				diffLower;
	vec_pair::iterator	insertIt;
	
	for (std::vector<size_t>::const_iterator it = jSuit.begin();
		it != jSuit.end(); ++it)
	{
		int i;
		i = *it;
		if (diff >= mainChain.size())
			diff = mainChain.size();
		diffLower = diff;
		for (vec_pair::iterator it2 = mainChain.begin() + diff;it2 != mainChain.end() &&  *((*it2).end() - 1) != i ; --it2) {
			--diffLower;
		}
		int diffP = (i * 2) + 1;
		insertIt = std::lower_bound(mainChain.begin(), mainChain.begin() + diffLower, *(index + diffP));
		mainChain.insert(insertIt, *(index + (i * 2) + 1));
		++diff;
		if ((it + 1) != jSuit.end() && *it < *(it + 1)) {
			diff += *(it + 1);
		}
	}
}

static void
FJInsertion(std::vector<size_t> const jSuit, vec_pair &pair) {
	vec_pair::iterator	index = pair.begin();
	vec_pair			mainChain;
	
	newMainChain(mainChain, pair);
	FJInsertionLoop(jSuit, mainChain, index);
	pair.clear();
	pair = mainChain;
}

static void
cleanChain(PmergeMe &p, vec_pair const&pair, size_t &level) {
	p.clearChain();
	p.setChain(pair);
	p.removeIndex();
	if (level == 0)
		p.cleanData();
}

void
PmergeMe::fordJohnson() {
	static size_t		level = 0;
	vec_int				leftOver;
	std::vector<size_t>	jSuit;
	vec_pair			pair;
	
	if (this->getChain().size() <= 1)
		return ;
	leftOver = this->sortPair();
	this->makePair();
	++level;
	this->fordJohnson();
	--level;
	size_t			comp = pow(2, level);
	this->dividePair_indexation(comp);
	pair = this->getChain();
	jSuit = PmergeMe::buildJacobsthalOrder(pair.size() / 2);
	FJInsertion(jSuit, pair);
	if (!leftOver.empty())
		LOinsertion(pair, leftOver);
	cleanChain(*this, pair, level);
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
    size_t prev = 1;
    for (size_t k = 1; k < t.size(); ++k)
    {
        size_t curr = t[k];
        size_t high = curr < n ? curr : n;
        for (size_t i = high; i > prev; --i)
            order.push_back(i - 1);
        prev = curr;
        if (curr >= n)
            break;
    }
    return order;
}

void
PmergeMe::setRawDeq(deq_int input) {
	this->_rawDeq = input;
}

void
PmergeMe::setChainDeq(deq_pair input) {
	this->_chainDeq = input;
}

void
PmergeMe::clearChainDeq() {
	(this->_chainDeq).clear();
}

void
PmergeMe::pushBackChainDeq(deq_int &vec) {
	(this->_chainDeq).push_back(vec);
}

deq_int
PmergeMe::getRawDeq() const {
	return this->_rawDeq;
}

deq_pair
PmergeMe::getChainDeq() const {
	return this->_chainDeq;
}

deq_int const 
PmergeMe::sortPairDeq() {
	deq_pair			pair = this->getChainDeq();
	deq_pair::iterator	it = pair.begin();
	deq_int				leftOver;

	for (;it != pair.end(); it += 2) {
		if ((it + 1) == pair.end()) {
			leftOver = *it;
			pair.pop_back();
			break; 
		}
		if (*it < *(it + 1))
			std::swap(*it, *(it + 1));
	}
	this->setChainDeq(pair);
	return leftOver;
}

void
PmergeMe::dividePair_indexationDeq(size_t comp) {
	deq_int tmp;
	deq_int tmp2;
	deq_pair pair = this->getChainDeq();
	deq_pair::iterator it = pair.begin();

	this->clearChainDeq();
	for (int i = 0; it != pair.end(); ++it, ++i) {
		tmp.insert(tmp.end(), (*it).begin(), (*it).begin() + comp);
		tmp.push_back(i);
		tmp2.insert(tmp2.end(), (*it).begin() + comp, (*it).end());
		tmp2.push_back(i);
		this->pushBackChainDeq(tmp);
		this->pushBackChainDeq(tmp2);
		tmp.clear();
		tmp2.clear();
	}
}

void
PmergeMe::removeIndexDeq() {
	deq_pair pair = this->getChainDeq();
	deq_pair::iterator it = pair.begin();

	this->clearChainDeq();
	for (; it != pair.end(); ++it) {
		(*it).pop_back();
	}
	this->setChainDeq(pair);
}

void
PmergeMe::makePairDeq() {
	deq_int tmp;
	deq_pair pair = this->getChainDeq();
	deq_pair::iterator it = pair.begin();

	this->clearChainDeq();
	for (; it != pair.end(); it += 2) {
		tmp.insert(tmp.end(), (*it).begin(), (*it).end());
		tmp.insert(tmp.end(), (*(it + 1)).begin(), (*(it + 1)).end());
		this->pushBackChainDeq(tmp);
		tmp.clear();
	}
}

void
PmergeMe::cleanDataDeq() {
	deq_pair	chain;
	deq_int		raw;

	chain = this->getChainDeq();
	for (deq_pair::iterator it = chain.begin(); it != chain.end(); ++it) {
		raw.push_back(*(it->begin()));
	}
	this->setRawDeq(raw);
}

static void
newMainChainDeq(deq_pair &v, deq_pair const &pair) {
	PmergeMe	tmp;
	int i;
	deq_pair	p;
	deq_int		tmpV;

	tmp.setChainDeq(pair);
	tmp.removeIndexDeq();
	p = tmp.getChainDeq();
	i = 0;
	for (deq_pair::const_iterator	it = p.begin(); it != p.end(); it += 2)
	{
		if (it + 1 == p.end()) {
			std::cout << "Problem"  << std::endl;
			break;
		}
		tmpV = *it;
		tmpV.push_back(i);
		v.push_back(tmpV);
		tmpV.clear();
		++i;
	}
}

static void
LOinsertionDeq(deq_pair &pair, deq_int &lo) {
	deq_pair::iterator it = std::lower_bound(pair.begin(), pair.end(), lo);
	lo.push_back(-42);
	pair.insert(it, lo);
}

static void
FJInsertionLoopDeq(std::deque<size_t> const &jSuit, deq_pair &mainChain, deq_pair::iterator const	&index) {
	size_t				diff = 0;
	size_t				diffLower;
	deq_pair::iterator	insertIt;
	
	for (std::deque<size_t>::const_iterator it = jSuit.begin();
		it != jSuit.end(); ++it)
	{
		int i;
		i = *it;
		if (diff >= mainChain.size())
			diff = mainChain.size();
		diffLower = diff;
		for (deq_pair::iterator it2 = mainChain.begin() + diff;it2 != mainChain.end() &&  *((*it2).end() - 1) != i ; --it2) {
			--diffLower;
		}
		int diffP = (i * 2) + 1;
		insertIt = std::lower_bound(mainChain.begin(), mainChain.begin() + diffLower, *(index + diffP));
		mainChain.insert(insertIt, *(index + (i * 2) + 1));
		++diff;
		if ((it + 1) != jSuit.end() && *it < *(it + 1)) {
			diff += *(it + 1);
		}
	}
}

static void
FJInsertionDeq(std::deque<size_t> const jSuit, deq_pair &pair) {
	deq_pair::iterator	index = pair.begin();
	deq_pair			mainChain;
	
	newMainChainDeq(mainChain, pair);
	FJInsertionLoopDeq(jSuit, mainChain, index);
	pair.clear();
	pair = mainChain;
}

static void
cleanChainDeq(PmergeMe &p, deq_pair const&pair, size_t &level) {
	p.clearChainDeq();
	p.setChainDeq(pair);
	p.removeIndexDeq();
	if (level == 0)
		p.cleanDataDeq();
}

void
PmergeMe::fordJohnsonDeq() {
	static size_t		level = 0;
	deq_int				leftOver;
	std::deque<size_t>	jSuit;
	deq_pair			pair;
	
	if (this->getChainDeq().size() <= 1)
		return ;
	leftOver = this->sortPairDeq();
	this->makePairDeq();
	++level;
	this->fordJohnsonDeq();
	--level;
	size_t			comp = pow(2, level);
	this->dividePair_indexationDeq(comp);
	pair = this->getChainDeq();
	jSuit = PmergeMe::buildJacobsthalOrderDeq(pair.size() / 2);
	FJInsertionDeq(jSuit, pair);
	if (!leftOver.empty())
		LOinsertionDeq(pair, leftOver);
	cleanChainDeq(*this, pair, level);
	return ;
}

std::deque<size_t>
PmergeMe::buildJacobsthalOrderDeq(size_t n)
{
     std::deque<size_t> order;
	 
	order.push_back(0);
    if (n <= 1)
        return order;
    std::deque<size_t> t;
    t.push_back(1);
    t.push_back(3);
    while (t.back() < n)
        t.push_back(t[t.size()-1] + 2 * t[t.size()-2]);
    size_t prev = 1;
    for (size_t k = 1; k < t.size(); ++k)
    {
        size_t curr = t[k];
        size_t high = curr < n ? curr : n;
        for (size_t i = high; i > prev; --i)
            order.push_back(i - 1);
        prev = curr;
        if (curr >= n)
            break;
    }
    return order;
}


