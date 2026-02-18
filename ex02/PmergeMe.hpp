/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmory <tmory@student.42antananarivo.mg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 11:32:26 by tmory             #+#    #+#             */
/*   Updated: 2026/02/18 03:09:20 by tmory            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP
# include <iostream>
# include <string>
# include <vector>
# include <deque>
# include <sstream>
# include <algorithm>
# include <cmath>
#include <sys/time.h>
#include <iomanip>
# define NO_PAIR	-1

typedef std::vector<int> vec_int;
typedef std::deque<int> deq_int;
typedef std::vector<vec_int> vec_pair;
typedef std::deque<deq_int> deq_pair;

class PmergeMe
{
private:
	vec_int		_rawVec;
	deq_int	_rawDeq;
	vec_pair	_chain;
	deq_pair	_chainDeq;
private:
	PmergeMe(PmergeMe const &src);
	PmergeMe &operator=(PmergeMe const &rhs);
public:
	PmergeMe();
	~PmergeMe();
	void	setRaw(vec_int input);
	void	setChain(vec_pair input);
	void	clearChain();
	void	pushBackChain(vec_int &);
	vec_int	getRaw() const;
	vec_pair	getChain() const;
	void		fordJohnson();
	static std::vector<size_t>	buildJacobsthalOrder(size_t n);
	vec_int const	sortPair();
	void 			dividePair_indexation(size_t comp);
	void			removeIndex();
	void 			makePair();
	void			cleanData();
	
	void	setRawDeq(deq_int input);
	void	setChainDeq(deq_pair input);
	void	clearChainDeq();
	void	pushBackChainDeq(deq_int &);
	deq_int	getRawDeq() const;
	deq_pair	getChainDeq() const;
	void		fordJohnsonDeq();
	static std::deque<size_t>	buildJacobsthalOrderDeq(size_t n);
	deq_int const	sortPairDeq();
	void 			dividePair_indexationDeq(size_t comp);
	void			removeIndexDeq();
	void 			makePairDeq();
	void			cleanDataDeq();

	template <typename T, typename U>
	static void
	printP(T cont) {
		typename T::const_iterator it = cont.begin();
		for (; it != cont.end(); it += 2) {
			typename U::const_iterator it2 = (*it).begin();
			if (it + 1 == cont.end()) {
				std::cout << "[";
				for (; it2 != (*it).end(); ++it2) {
					std::cout << *it2;
					if (it2 + 1 != (*it).end())
						std::cout << ",";
				}
				std::cout << "]:[NO_PAIR]" << std::endl;
				break;
			}
			typename U::const_iterator it3 = (*(it + 1)).begin();
			std::cout << "[";
			for (; it2 != (*it).end(); ++it2) {
				std::cout << *it2;
				if (it2 + 1 != (*it).end())
					std::cout << ",";
			}
			std::cout << "]:[";
			for (; it3 != (*(it + 1)).end(); ++it3) {
				std::cout << *it3;
				if (it3 + 1 != (*(it + 1)).end())
					std::cout << ",";
			}
			std::cout << "]";
			std::cout << std::endl;
		}
	}

	template <typename T>
	static void
	printC(T cont) {
		typename T::iterator it = cont.begin();
		for (; it != cont.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;
	}
};

#endif
