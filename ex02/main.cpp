/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmory <tmory@student.42antananarivo.mg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 11:33:09 by tmory             #+#    #+#             */
/*   Updated: 2026/02/18 03:18:05 by tmory            ###   ########.fr       */
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

void
push_back_toPairDeq(deq_pair &arrayP, deq_int const & array)
{
	deq_int::const_iterator	it = array.begin();
	deq_int					tmp;
	
	for (; it != array.end(); ++it) {
		tmp.push_back(*it);
		arrayP.push_back(tmp);
		tmp.clear();
	}
}

bool
FJSuitDataDeq(deq_int const &array, PmergeMe &pmerge) {
	deq_pair				arrayP;
	
	if(array.empty())
		return false; 
	push_back_toPairDeq(arrayP, array);
	pmerge.setChainDeq(arrayP);
	return true;
}

int main(int ac, char ** av) {
	vec_int				raw;
	std::stringstream	tmp;
	PmergeMe			pmerge;
	timeval				start, end;

	
	if (ac <= 1)
		return (std::cerr << "Error" << std::endl, 1);
	for (size_t i = 1; av[i]; ++i) {
		tmp << av[i];
		if (av[i + 1])
			tmp << ",";
	}
	if (!checkInput(raw, tmp))
		return (std::cerr << "Error" << std::endl, 1);
	deq_int	rawDeq(raw.begin(), raw.end());
	pmerge.setRaw(raw);
	std::cout << "Before :  ";
	PmergeMe::printC(pmerge.getRaw());
	if (!FJSuitData(raw, pmerge))
		return 1;
		
    gettimeofday(&start, NULL);
	pmerge.fordJohnson();
    gettimeofday(&end, NULL);
	long seconds  = end.tv_sec  - start.tv_sec;
    long useconds = end.tv_usec - start.tv_usec;
    if (useconds < 0)
	{
		--seconds;
		useconds += 1000000;
	}

	double totalUsVec = seconds + useconds / 1000000.0;

	std::cout << "After :  ";
	PmergeMe::printC(pmerge.getRaw());
	
	std::cout << "---------------------------" << std::endl;
	
	pmerge.setRawDeq(rawDeq);
	// std::cout << "Before :  ";
	// PmergeMe::printC(pmerge.getRawDeq());
	if (!FJSuitDataDeq(rawDeq, pmerge))
		return 1;
    gettimeofday(&start, NULL);
	pmerge.fordJohnsonDeq();
    gettimeofday(&end, NULL);
	seconds  = end.tv_sec  - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;
    if (useconds < 0)
	{
		--seconds;
		useconds += 1000000;
	}

	double totalUsDeq = seconds + useconds / 1000000.0;
	// std::cout << "After :  ";
	// PmergeMe::printC(pmerge.getRaw());
	std::cout << std::fixed << std::setprecision(5);
	std::cout << "Time to process a range of " <<  raw.size() << " elements with std::vector : " << totalUsVec << " us"<< std::endl;
	std::cout << "Time to process a range of " <<  rawDeq.size() << " elements with std::deque : " << totalUsDeq << " us"<< std::endl;
	
	// Time to process a range of 5 elements with std::[..] : 0.00031 us
	return 0;
}
