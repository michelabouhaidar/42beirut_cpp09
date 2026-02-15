/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 00:22:16 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/12/22 23:48:11 by mabou-ha         ###   ########.fr       */
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
		static int comparisonNumber_;
		PmergeMe();

		template <typename T>
		void mergeInsertionSort(T& cont);
};

long jacobstahlSequence(long n);

template <typename T>
static T iterJump(T it, int steps)
{
	std::advance(it, steps);
	return it;
}

template <typename T>
static void swapPairs(T it, int order)
{
	T leftStart = iterJump(it, -order + 1);
	T rightStart = iterJump(leftStart, order);
	for (int i = 0; i < order; ++i)
	{
		std::iter_swap(leftStart, rightStart);
		++rightStart;
		++leftStart;
	}
}

template <typename T>
static bool compareElements(T leftIterator, T rightIterator)
{
	PmergeMe::comparisonNumber_++;
	return *leftIterator < *rightIterator;
}

template <typename T>
static void mergeInsertSort(T& cont, int order)
{
	typedef typename T::iterator Iterator;

	int size = static_cast<int>(cont.size());
	int elementCount = size / order;

	if (elementCount < 2)
		return ;

	bool oddPairNumber = elementCount % 2 == 1;

	Iterator start = cont.begin();
	Iterator last = iterJump(cont.begin(), order * elementCount);
	Iterator end = iterJump(last, -(oddPairNumber * order));

	int jump = 2 * order;
	for (Iterator it = start; it != end; std::advance(it, jump))
	{
		Iterator currPair = iterJump(it, order - 1);
		Iterator nextPair = iterJump(it, order * 2 - 1);
		if (compareElements(nextPair, currPair))
		{
			swapPairs(currPair, order);
		}
	}
	mergeInsertSort(cont, order * 2);

	typedef std::vector<Iterator> IteratorContainer;

	IteratorContainer main;
	IteratorContainer pend;

	main.push_back(iterJump(cont.begin(), order - 1));
	main.push_back(iterJump(cont.begin(), order * 2 - 1));
	for (int i = 4; i <= elementCount; i += 2)
	{
		pend.push_back(iterJump(cont.begin(), order * (i - 1) - 1));
		main.push_back(iterJump(cont.begin(), order * i - 1));
	}
	if (oddPairNumber)
	{
		pend.push_back(iterJump(end, order - 1));
	}
	int prev_jack = jacobstahlSequence(1);
	int inserted_nb = 0;
	for (int k = 2;; k++)
	{
		int curr_jack = jacobstahlSequence(k);
		int diff_jack = curr_jack - prev_jack;
		int offset = 0;
		if (diff_jack <= 0)
		{
        	prev_jack = curr_jack;
        	continue;
		}
		if (diff_jack > static_cast<int>(pend.size()))
			break;
		int looping = diff_jack;
		typename IteratorContainer::iterator pend_it = iterJump(pend.begin(), diff_jack - 1);
		typename IteratorContainer::iterator bound_it = iterJump(main.begin(), curr_jack + inserted_nb);
		while (looping)
		{
			typename IteratorContainer::iterator idx = std::upper_bound(main.begin(), bound_it, *pend_it, compareElements<Iterator>);
			typename IteratorContainer::iterator inserted = main.insert(idx, *pend_it);
			pend_it = pend.erase(pend_it);
			looping--;
			if (looping)
				std::advance(pend_it, -1);
			offset += (inserted - main.begin()) == curr_jack + inserted_nb;
			bound_it = iterJump(main.begin(), curr_jack + inserted_nb - offset);
		}
		prev_jack = curr_jack;
		inserted_nb += diff_jack;
		offset = 0;
	}
	if (!pend.empty())
	{
		for (ssize_t i = pend.size() - 1; i >= 0; i--)
		{
			typename IteratorContainer::iterator curr_pend = iterJump(pend.begin(), i);
			typename IteratorContainer::iterator curr_bound = iterJump(main.begin(), main.size() - pend.size() + i + oddPairNumber);
			typename IteratorContainer::iterator idx = std::upper_bound(main.begin(), curr_bound, *curr_pend, compareElements<Iterator>);
			main.insert(idx, *curr_pend);
		}
	}
	std::vector<int> copy;
	copy.reserve(cont.size());
	for (typename IteratorContainer::iterator it = main.begin(); it != main.end(); it++)
	{
		for (int i = 0; i < order; i++)
		{
			Iterator pair_start = *it;
			std::advance(pair_start, -order + i + 1);
			copy.push_back(*pair_start);
		}
	}
	Iterator container_it = cont.begin();
	std::vector<int>::iterator copy_it = copy.begin();
	while (copy_it != copy.end())
	{
		*container_it = *copy_it;
		container_it++;
		copy_it++;
	}
}

template <typename T>
void PmergeMe::mergeInsertionSort(T& cont)
{
	comparisonNumber_ = 0;
	mergeInsertSort(cont, 1);
}

#endif
