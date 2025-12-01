/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 20:52:36 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/12/01 02:47:20 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

template <typename T>
void PmergeMe::mergeInsertionSort(T& cont)
{
	comparisonNumber_ = 0;
	mergeInsertSort(cont, 1);
}

template <typename T>
void PmergeMe::mergeInsertSort(T& cont, int order)
{
	typedef typename T::iterator Iterator;

	int size = static_cast<int>(cont.size());
	int pairCount = size / order;

	if (pairCount < 2)
		return ;

	bool oddPairNumber = pairCount % 2 == 1;

	Iterator start = cont.begin();
	Iterator last = iterJump(cont.begin(), order * pairCount);
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

	Iterator begin = cont.begin();
	main.insert(main.end(), iterJump(begin, order - 1));
	main.insert(main.end(), iterJump(begin, order * 2 - 1));
	for (int i = 4; i <= pairCount; i += 2)
	{
		pend.insert(pend.end(), iterJump(begin, order * (i - 1) - 1));
		main.insert(main.end(), iterJump(begin, order * i - 1));
	}
	if (oddPairNumber)
	{
		pend.insert(pend.end(), iterJump(end, order - 1));
	}

    std::cout << "Main chain (order = " << order << "): ";
    for (typename IteratorContainer::iterator it = main.begin();
         it != main.end(); ++it)
    {
        std::cout << *(*it) << " ";
    }
    std::cout << "\n";
    std::cout << "Pending chain (order = " << order << "): ";
    for (typename IteratorContainer::iterator it = pend.begin();
         it != pend.end(); ++it)
    {
        std::cout << *(*it) << " ";
    }
    std::cout << "\n";
}

template <typename T>
void PmergeMe::swapPairs(T it, int order)
{
	T leftStart = it;
	std::advance(it, -order + 1);
	T rightStart = it;
	std::advance(leftStart, order);
	for (int i = 0; i < order; ++i)
	{
		std::iter_swap(leftStart, rightStart);
		++rightStart;
		++leftStart;
	}
}

template <typename T>
T iterJump(T it, int steps)
{
	std::advance(it, steps);
	return it;
}

template <typename T>
bool compareElements(T leftIterator, T rightIterator)
{
	PmergeMe::comparisonNumber_++;
	return *leftIterator < *rightIterator;
}