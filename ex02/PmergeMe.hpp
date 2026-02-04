/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmory <tmory@student.42antananarivo.mg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 11:32:26 by tmory             #+#    #+#             */
/*   Updated: 2026/02/04 17:07:12 by tmory            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP
# include <iostream>
# include <string>
# include <vector>
# include <sstream>
# define NO_LEFTOVER -1;

typedef std::vector<int> vec_int;
typedef struct	s_pair{
	vec_int	bigPair;
	vec_int	smallPair;
	int		leftOver;
} t_pair;
// typedef std::vector<std::pair<int, int> > vec_pair;

class PmergeMe
{
private:
	vec_int			_input;
private:
	PmergeMe(PmergeMe const &src);
	PmergeMe &operator=(PmergeMe const &rhs);
public:
	PmergeMe();
	~PmergeMe();
	void	setInput(vec_int input);
	vec_int	getPair() const;
	static vec_int generateIndex(vec_int const &array);
	static void	fordJohnson(vec_int &chain, vec_int index);
};

#endif
