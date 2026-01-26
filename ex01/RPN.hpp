/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RNP.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmory <tmory@student.42antananarivo.mg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 15:18:04 by tmory             #+#    #+#             */
/*   Updated: 2026/01/26 16:29:18 by tmory            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP
# include <iostream>
# include <string>
# include <algorithm>
# include <stack>
# include <sstream>

class RPN {
private:
	std::stack<double> 	_pile;
	std::stringstream	_input;
	double				_result;
	RPN();
	RPN(RPN const &src);
	RPN					&operator=(RPN const &rhs);
public:
	RPN(std::string input);
	~RPN();
	void				calculRPN();
	double				getResult() const;
};

#endif
