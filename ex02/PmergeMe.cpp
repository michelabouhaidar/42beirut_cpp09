/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 00:22:13 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/12/22 23:50:31 by mabou-ha         ###   ########.fr       */
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

long jacobstahlSequence(long n)
{
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;
	long a = 0;
	long b = 1;
	for (long i = 2; i <= n; ++i)
    {
        long c = b + 2 * a;
        a = b;
        b = c;
    }
	return b;
}