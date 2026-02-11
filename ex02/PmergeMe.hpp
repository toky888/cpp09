/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmory <tmory@student.42antananarivo.mg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 11:32:26 by tmory             #+#    #+#             */
/*   Updated: 2026/02/11 18:47:11 by tmory            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP
# include <iostream>
# include <string>
# include <vector>
# include <sstream>
# include <algorithm>
# define NO_PAIR	-1;
// # define SORT		true;
// # define NO_SORT		true;


typedef std::vector<int> vec_int;
typedef std::vector<vec_int> vec_pair;
// typedef std::vector<std::pair<int, int> > vec_pair;

class PmergeMe
{
private:
	vec_int			_raw;
private:
	PmergeMe(PmergeMe const &src);
	PmergeMe &operator=(PmergeMe const &rhs);
public:
	PmergeMe();
	~PmergeMe();
	void	setRaw(vec_int input);
	vec_int	getRaw() const;
	static void	fordJohnson(vec_int &chain);

	// template <typename T>
	// static void
	// printP(T const &cont) {
	// 	typename T::const_iterator it = cont.begin();
	// 	for (; it != cont.end(); ++it) {
	// 		std::cout << it->first << ":" << it->second << " , ";
	// 	}
	// 	std::cout << std::endl;
		
	// }

	template <typename T>
	static void
	printC(T cont) {
		typename T::iterator it = cont.begin();
		for (; it != cont.end(); ++it) {
			std::cout << *it << ",";
		}
		std::cout << std::endl;
	}
};

#endif
