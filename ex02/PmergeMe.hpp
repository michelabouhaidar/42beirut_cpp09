/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 00:22:16 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/12/01 02:47:25 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <deque>
# include <vector>
# include <algorithm>
# include <iterator>

class PmergeMe
{
	public:
		PmergeMe();
		PmergeMe(const PmergeMe& obj);
		PmergeMe& operator=(const PmergeMe& obj);
		~PmergeMe();

		template <typename T>
		void mergeInsertionSort(T& cont);

		static int comparisonNumber_;
	private:
		template <typename T>
		void swapPairs(T it, int order);
		
		template <typename T>
		void mergeInsertSort(T& cont, int order);
};

template <typename T>
T iterJump(T it, int steps);

template <typename T>
bool compareElements(T leftIterator, T rightIterator);

# include "PmergeMe.tpp"

#endif
