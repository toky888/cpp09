/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmory <tmory@student.42antananarivo.mg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 11:33:09 by tmory             #+#    #+#             */
/*   Updated: 2026/02/04 17:08:05 by tmory            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

template <typename T>
static void
printC(T cont) {
	typename T::iterator it = cont.begin();
	for (; it != cont.end(); ++it) {
		std::cout << *it << ",";
	}
	std::cout << std::endl;
}

template <typename T>
static void
printP(T const &cont) {
	typename T::const_iterator it = cont.begin();
	for (; it != cont.end(); ++it) {
		std::cout << *it << ":";
		if (it + 1 != cont.end()) {
			std::cout << *(it + 1) << std::endl;
			++it;	
		}	
		else
			std::cout << -1 << std::endl;
			
	}
	
}

std::vector<size_t>
buildJacobsthalOrder(size_t n)
{
     std::vector<size_t> order;
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
	mergeInsertionAlgo.setInput(raw);
	printC(buildJacobsthalOrder(mergeInsertionAlgo.getPair().size()));
	std::cout << "---------------------------" << std::endl;
	printP(mergeInsertionAlgo.getPair());
	std::cout << "---------------------------" << std::endl;
	
	printC(PmergeMe::generateIndex(raw));
	std::cout << "---------------------------" << std::endl;
	raw = mergeInsertionAlgo.getPair();
	PmergeMe::fordJohnson(raw, PmergeMe::generateIndex(raw));
	// printC(buildJacobsthalOrder(3));
	// printC(buildJacobsthalOrder(1000));
	// if (!raw.empty())
	// 	printC<std::vector<int> >(raw); //TEST
	// try {
	// }
	// catch(const std::exception& e) {
	// 	std::cerr << e.what() << '\n';
	// }
	
	return 0;
}
