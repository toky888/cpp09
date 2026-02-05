/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmory <tmory@student.42antananarivo.mg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 11:32:26 by tmory             #+#    #+#             */
/*   Updated: 2026/02/05 11:26:57 by tmory            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP
# include <iostream>
# include <string>
# include <vector>
# include <sstream>
# include <algorithm>
# define NO_LEFTOVER -1;

typedef std::vector<int> vec_int;
typedef std::vector<int, int> vec_pair;
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
	static vec_int generateIndex(size_t size);
	static void	fordJohnson(vec_int &chain, vec_int index);

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
