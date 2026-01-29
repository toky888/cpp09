/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmory <tmory@student.42antananarivo.mg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 11:33:09 by tmory             #+#    #+#             */
/*   Updated: 2026/01/29 14:49:55 by tmory            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

template <typename T>
static void
printC(T cont) {
	typename T::iterator it = cont.begin();
	for (; it != cont.end(); ++it) {
		std::cout << *it << " " << std::endl;
	}
}

template <typename T>
static void
printP(T const &cont) {
	typename T::const_iterator it = cont.begin();
	for (; it != cont.end(); ++it) {
		std::cout << it->first << ":" << it->second << std::endl;
	}
	
}

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

int main(int ac, char ** av) {
	std::vector<int>	raw;
	std::stringstream	tmp;
	size_t				i;
	PmergeMe			mergeInsertionAlgo;
	
	if (ac <= 1)
		return (std::cerr << "Error" << std::endl, 1);
	for (i = 1; av[i]; ++i) {
		tmp << av[i];
		if (av[i + 1])
			tmp << ",";
	}
	if (!checkInput(raw, tmp))
		return (std::cerr << "Error" << std::endl, 1);
	
	// if (!raw.empty())
	// 	printC<std::vector<int> >(raw); //TEST
	try {
		mergeInsertionAlgo.pair(raw);
		printP(mergeInsertionAlgo.getPair());
	}
	catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
	
	return 0;
}
