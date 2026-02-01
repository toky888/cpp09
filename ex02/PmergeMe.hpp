/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmory <tmory@student.42antananarivo.mg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 11:32:26 by tmory             #+#    #+#             */
/*   Updated: 2026/02/01 13:32:44 by tmory            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP
# include <iostream>
# include <string>
# include <vector>
# include <sstream>
# define NO_PAIR -1

typedef std::vector<int> vec_int;
typedef std::vector<std::pair<int, int> > vec_pair;

class PmergeMe
{
private:
	vec_pair	_pairVector;
private:
	PmergeMe(PmergeMe const &src);
	PmergeMe &operator=(PmergeMe const &rhs);
public:
	PmergeMe();
	~PmergeMe();
	vec_pair	getPair()const;
	void 		pair(vec_int const &input);
};

#endif
