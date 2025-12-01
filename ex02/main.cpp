/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 00:22:18 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/12/01 02:48:39 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <stdexcept>
#include <climits>
#include <cctype>
#include <sstream>
#include <cstdlib>

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
static bool isSorted(const T& cont)
{
	if (cont.size() < 1)
		return true;
	typename T::const_iterator it = cont.begin();
	typename T::const_iterator prev = it++;
	for (; it != cont.end(); ++it, ++prev)
	{
		if (*prev > *it)
			return false;
	}
	return true;
}

// static std::string argvToString(int argc, char **argv)
// {
// 	std::string str;
// 	str += "[";
// 	if (argc > 1)
// 	{
// 		str += argv[1];
// 		for (int i = 2; argv[i]; ++i)
// 		{
// 			str += " ";
// 			str += argv[i];
// 		}
// 	}
// 	str += "]";
// 	return str;
// }

template <typename T>
static std::string containerToString(T& cont)
{
	std::stringstream ss;
	ss << "[";
	typename T::const_iterator it = cont.begin();
	typename T::const_iterator end = cont.end();

	if (it != end)
	{
		ss << *it;
		++it;
	}
	for (; it != end; ++it)
	{
		ss << " " << *it;
	}
	ss << "]";
	return ss.str();
}

int main(int argc, char **argv)
{
    try
    {
        validate_arguments(argc, argv);

        std::vector<int> v = argvToContainer<std::vector<int> >(argc, argv);
        std::deque<int>  d = argvToContainer<std::deque<int> >(argc, argv);

        std::cout << "Before:  " << containerToString(v) << "\n";


        PmergeMe sorter;
		sorter.mergeInsertionSort(v);
		sorter.mergeInsertionSort(d);
			
		std::cout << "After:   " << containerToString(v) << "\n";
		std::cout << "Sorted?  " << (isSorted(v) ? "yes" : "no") << "\n";
			
		std::cout << "Comparisons: " << PmergeMe::comparisonNumber_ << "\n";

    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}