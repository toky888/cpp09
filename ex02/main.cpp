/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmory <tmory@student.42antananarivo.mg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 11:33:09 by tmory             #+#    #+#             */
/*   Updated: 2026/02/16 15:58:33 by tmory            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"





static void
trim_char(std::string& s, char c)
{
    while (!s.empty() && s[0] == c)
        s.erase(0, 1);
    while (!s.empty() && s[s.size() - 1] == c)
        s.erase(s.size() - 1, 1);
}

static bool
checkInput(std::vector<int> &raw, std::stringstream &tmp) {
	std::string	numStr;
	int			num;
	
	num = 0;
	while (getline(tmp, numStr, ',')) {
		trim_char(numStr, ' ');
		std::stringstream	tmpStream;
		tmpStream << numStr;
		if (!(tmpStream >> num))
			return false;
		if (!tmpStream.eof())
			return false;
		if (num < 0)
			return false;
		raw.push_back(num);
	}
	return true;
}

void
push_back_toPair(vec_pair &arrayP, vec_int const & array)
{
	vec_int::const_iterator	it = array.begin();
	vec_int					tmp;
	
	for (; it != array.end(); ++it) {
		tmp.push_back(*it);
		arrayP.push_back(tmp);
		tmp.clear();
	}
	
}

bool
FJSuitData(vec_int const &array, PmergeMe &pmerge) {
	vec_pair				arrayP;
	
	if(array.empty())
		return false; 
	push_back_toPair(arrayP, array);
	pmerge.setChain(arrayP);
	return true;
}

int main(int ac, char ** av) {
	vec_int				raw;
	vec_pair			pair;
	std::stringstream	tmp;
	PmergeMe			pmerge;
	
	if (ac <= 1)
		return (std::cerr << "Error" << std::endl, 1);
	for (size_t i = 1; av[i]; ++i) {
		tmp << av[i];
		if (av[i + 1])
			tmp << ",";
	}
	if (!checkInput(raw, tmp))
		return (std::cerr << "Error" << std::endl, 1);
	
	pmerge.setRaw(raw);
	std::cout << "Jacobsthal suite :" << std::endl;
	PmergeMe::printC(PmergeMe::buildJacobsthalOrder(pmerge.getRaw().size()));
	std::cout << "---------------------------" << std::endl;
	std::cout << "raw suite :" << std::endl;
	PmergeMe::printC(raw);
	std::cout << "pmerge raw suite :" << std::endl;
	PmergeMe::printC(pmerge.getRaw());
	std::cout << "---------------------------" << std::endl;
	
	if (!FJSuitData(raw, pmerge))
		return 1;
	std::cout << "pair suite :" << std::endl;
	PmergeMe::printP<vec_pair, vec_int>(pmerge.getChain());

	
	pmerge.fordJohnson();
	return 0;
}
