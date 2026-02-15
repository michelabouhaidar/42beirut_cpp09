/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 00:22:18 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/12/23 00:01:08 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

#include <iostream>
#include <vector>
#include <deque>
#include <stdexcept>
#include <climits>
#include <cstdlib>
#include <cctype>
#include <ctime>
#include <iomanip>

static void validate_arguments(int argc, char **argv)
{
	if (argc < 2)
		throw std::runtime_error("Error: at least one number is required");
	for (int i = 1; i < argc; ++i)
	{
		std::string s(argv[i]);
		if (s.empty())
			throw std::runtime_error("Error: empty argument");
		for (std::string::size_type j = 0; j < s.size(); ++j)
		{
			if (!std::isdigit(static_cast<unsigned char>(s[j])))
				throw std::runtime_error("Error: only positive integers are allowed");
		}
		char *end = 0;
		long val = std::strtol(s.c_str(), &end, 10);
		if (*end != '\0')
			throw std::runtime_error("Error: invalid numeric argument");
		if (val < 0 || val > INT_MAX)
			throw std::runtime_error("Error: integer out of range");
	}
}

template <typename T>
static T argvToContainer(int argc, char **argv)
{
	T cont;
	for (int i = 1; i < argc; ++i)
	{
		char *end = 0;
		long val = std::strtol(argv[i], &end, 10);
		cont.push_back(static_cast<int>(val));
	}
	return cont;
}

template <typename T>
static void printContainerPreview(const T& cont, std::size_t previewCount)
{
	std::size_t n = cont.size();
	typename T::const_iterator it = cont.begin();
	if (n <= previewCount)
	{
		for (std::size_t i = 0; i < n; ++i, ++it)
		{
			if (i) std::cout << " ";
			std::cout << *it;
		}
		return;
	}
	for (std::size_t i = 0; i < previewCount; ++i, ++it)
	{
		if (i) std::cout << " ";
		std::cout << *it;
	}
	std::cout << " [...]";
}

static double elapsed_us(std::clock_t start, std::clock_t end)
{
	return (static_cast<double>(end - start) * 1000000.0) / static_cast<double>(CLOCKS_PER_SEC);
}

int main(int argc, char **argv)
{
	try
	{
		validate_arguments(argc, argv);

		std::vector<int> v = argvToContainer< std::vector<int> >(argc, argv);
		std::deque<int>  d = argvToContainer< std::deque<int> >(argc, argv);

		std::cout << "Before: ";
		printContainerPreview(v, 100);
		std::cout << "\n";

		PmergeMe sorter;

		std::clock_t v_start = std::clock();
		sorter.mergeInsertionSort(v);
		int v_count = sorter.comparisonNumber_;
		std::clock_t v_end = std::clock();

		std::clock_t d_start = std::clock();
		sorter.mergeInsertionSort(d);
		int d_count = sorter.comparisonNumber_;
		std::clock_t d_end = std::clock();

		std::cout << "After:  ";
		printContainerPreview(v, 100);
		std::cout << "\n";

		const std::size_t n = v.size();

		std::cout << "Time to process a range of " << n
		          << " elements with std::vector : "
		          << std::fixed << std::setprecision(5)
		          << elapsed_us(v_start, v_end) << " us\n";

		std::cout << "Number of comprisons in the process of" << n
				  << " elements with std::vector : " << v_count << std::endl;

		std::cout << "Time to process a range of " << n
		          << " elements with std::deque : "
		          << std::fixed << std::setprecision(5)
		          << elapsed_us(d_start, d_end) << " us\n";

		std::cout << "Number of comprisons in the process of" << n
				  << " elements with std::deque : " << d_count << std::endl;
	}
	catch (const std::exception&)
	{
		std::cerr << "Error" << std::endl;
		return 1;
	}
	return 0;
}