/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmory <tmory@student.42antananarivo.mg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 11:34:40 by tmory             #+#    #+#             */
/*   Updated: 2026/01/29 14:52:09 by tmory            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {}

vec_pair
PmergeMe::getPair() const {
	return this->_pair;
}

void
PmergeMe::pair(vec_int const &input) {
	vec_int::const_iterator	it = input.begin();

	for (; it != input.end(); ++it) {
		if (it + 1 == input.end())
			this->_pair.push_back(std::make_pair(*it, NO_PAIR));
		else {
			if (*it > *(it + 1))
				this->_pair.push_back(std::make_pair(*it, *(it + 1)));
			else
				this->_pair.push_back(std::make_pair(*(it + 1), *it));
			++it;
		}	
	}
	// if (this->_pair.empty())
	// 	std::cout << "THI IS A TEST"  << std::endl;
}
