/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 21:18:24 by mabou-ha          #+#    #+#             */
/*   Updated: 2026/02/15 00:00:00 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cctype>
#include <iomanip>
#include <stdexcept>

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const std::string& dbFile)
{
	localDatabase(dbFile);
}

static std::string trim(const std::string& s)
{
	std::string::size_type start = 0;
	while (start < s.size() && (s[start] == ' ' || s[start] == '\t'))
		++start;
	std::string::size_type end = s.size();
	while (end > start && (s[end - 1] == ' ' || s[end - 1] == '\t'))
		--end;
	return s.substr(start, end - start);
}

static bool isValidDateFormat(const std::string& date)
{
	if (date.length() != 10)
		return false;
	for (std::string::size_type i = 0; i < date.length(); i++)
	{
		if (i == 4 || i == 7)
		{
			if (date[i] != '-')
				return false;
		}
		else
		{
			if (!std::isdigit(static_cast<unsigned char>(date[i])))
				return false;
		}
	}
	return true;
}

static bool isValidDate(const std::string& date)
{
	if (!isValidDateFormat(date))
		return false;
	int year = std::atoi(date.substr(0, 4).c_str());
	int mon = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());
	if (mon < 1 || mon > 12)
		return false;
	int month_days;
	if (mon == 1 || mon == 3 || mon == 5 || mon == 7 || mon == 8 || mon == 10 || mon == 12)
		month_days = 31;
	else if (mon == 4 || mon == 6 || mon == 9 || mon == 11)
		month_days = 30;
	else
	{
		if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
			month_days = 29;
		else
			month_days = 28;
	}
	if (day < 1 || day > month_days)
		return false;
	return true;
}

static bool parseValue(const std::string& str, double& value)
{
	if (str.empty())
		return false;
	std::istringstream iss(str);
	iss >> value;
	if (iss.fail())
		return false;
	char c;
	if (iss >> c)
		return false;
	return true;
}

static bool getRateForDate(std::map<std::string, double> map, const std::string& date, double &rate)
{
	if (map.empty())
		return false;
	std::map<std::string, double>::const_iterator it = map.lower_bound(date);
	if (it == map.end())
		--it;
	else if (it->first != date)
	{
		if (it == map.begin())
			return false;
		--it;
	}
	rate = it->second;
	return true;
}

void BitcoinExchange::localDatabase(const std::string &dbFile)
{
	std::ifstream file(dbFile.c_str());
	if (!file.is_open())
		throw std::runtime_error("Error: could not open database file.");
	std::string line;
	if (!std::getline(file, line))
		throw std::runtime_error("Error: empty database file.");
	while (std::getline(file, line))
	{
		if (line.empty())
			continue;
		std::string::size_type comma = line.find(',');
		if (comma == std::string::npos)
			continue;
		std::string date = trim(line.substr(0, comma));
		std::string valueStr = trim(line.substr(comma + 1));
		if (!isValidDate(date))
			continue;
		double rate;
		if (!parseValue(valueStr, rate))
			continue;
		rates_[date] = rate;
	}
	if (rates_.empty())
		throw std::runtime_error("Error: database contains no valid data.");
}

static bool hasStrictPipe(const std::string& line, std::string::size_type& pos)
{
	pos = line.find('|');
	if (pos == std::string::npos)
		return false;
	if (pos == 0 || pos + 1 >= line.size())
		return false;
	if (line[pos - 1] != ' ' || line[pos + 1] != ' ')
		return false;
	return true;
}

void BitcoinExchange::processInput(const std::string &inputFile) const
{
	std::ifstream file(inputFile.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return;
	}
	std::string line;
	if (!std::getline(file, line))
		return;
	while (std::getline(file, line))
	{
		if (line.empty())
			continue;

		const std::string original = line;
		std::string::size_type pipePos;
		if (!hasStrictPipe(line, pipePos))
		{
			std::cerr << "Error: bad input => " << original << std::endl;
			continue;
		}
		std::string date = trim(line.substr(0, pipePos));
		std::string valueStr = trim(line.substr(pipePos + 1));
		if (!isValidDate(date))
		{
			std::cerr << "Error: bad input => " << date << std::endl;
			continue;
		}
		double value;
		if (!parseValue(valueStr, value))
		{
			std::cerr << "Error: bad input => " << valueStr << std::endl;
			continue;
		}
		if (value < 0)
		{
			std::cerr << "Error: not a positive number." << std::endl;
			continue;
		}
		if (value > 1000)
		{
			std::cerr << "Error: too large a number." << std::endl;
			continue;
		}
		double rate;
		if (!getRateForDate(rates_, date, rate))
		{
			std::cerr << "Error: bad input => " << original << std::endl;
			continue;
		}
		std::cout << date << " => " << value << " = " << (value * rate) << std::endl;
	}
}