/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RNP.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmory <tmory@student.42antananarivo.mg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 15:18:04 by tmory             #+#    #+#             */
/*   Updated: 2026/01/23 16:37:09 by tmory            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RNP_HPP
# define RNP_HPP
# include <iostream>
# include <string>
# include <algorithm>
# include <stack>
# include <sstream>

class RNP {
private:
	std::stack<int> 	_pile;
	RNP ();
	RNP (RNP const &src);
	RNP &operator=(RNP const &rhs);
public:
	RNP (std::string input);
	~RNP ();
};

#endif
