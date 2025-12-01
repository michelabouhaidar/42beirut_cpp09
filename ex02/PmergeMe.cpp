/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 00:22:13 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/12/01 02:47:28 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int PmergeMe::comparisonNumber_ = 0;

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& obj) {(void) obj;}

PmergeMe& PmergeMe::operator=(const PmergeMe& obj)
{
	(void) obj;
	return*this;
}

PmergeMe::~PmergeMe() {}