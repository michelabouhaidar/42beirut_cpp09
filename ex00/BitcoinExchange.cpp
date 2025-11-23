/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 21:18:24 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/11/24 00:19:36 by mabou-ha         ###   ########.fr       */
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

BitcoinExchange::BitcoinExchange(const BitcoinExchange& obj): rates_(obj.rates_) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& obj)
{
	if (this != &obj)
		rates_ = obj.rates_;
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

std::string BitcoinExchange::trim(const std::string& s) const
{
	std::string::size_type start = 0;
	while (start < s.size() && (s[start] == ' ' || s[start] == '\t'))
		++start;
	std::string::size_type end = s.size();
	while (end > start && (s[end - 1] == ' ' || s[end - 1] == '\t'))
		--end;
	return s.substr(start, end - start);
}

bool BitcoinExchange::isValidDateFormat(const std::string& date) const
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
			if(!std::isdigit(static_cast<unsigned int>(date[i])))
				return false;
		}
	}
	return true;
}

bool BitcoinExchange::isValidDate(const std::string& date) const
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
		if ((year  % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
			month_days = 29;
		else
			month_days = 28;
	}
	if ( day < 1 || day > month_days)
		return false;
	return true;
}

bool BitcoinExchange::parseValue(const std::string& str, double& value) const
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

bool BitcoinExchange::getRateForDate(const std::string& date, double &rate) const
{
	if (rates_.empty())
		return false;
	std::map<std::string, double>::const_iterator it = rates_.lower_bound(date);
	if (it == rates_.end())
		--it;
	else if (it->first != date)
	{
		if (it == rates_.begin())
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

void BitcoinExchange::processInput(const std::string &inputFile) const
{
	std::ifstream file(inputFile.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: could not opne file." << std::endl;
		return;
	}
	std::string line;
	if (!std::getline(file, line))
		return;
	while (std::getline(file, line))
	{
		if (line.empty())
			continue;
		std::string::size_type pipePos = line.find('|');
		if (pipePos == std::string::npos)
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}
		std::string date = trim(line.substr(0, pipePos));
		std::string valueStr = trim(line.substr(pipePos + 1));
		if (!isValidDate(date))
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}
		double value;
		if (!parseValue(valueStr, value))
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}
		if (value < 0)
		{
			std::cerr << "Error: not a positive number." << std::endl;
			continue;
		}
		if (value > 1000)
		{
			std::cerr << "Error: too large number." << std::endl;
			continue;
		}
		double rate;
		if (!getRateForDate(date, rate))
		{
			std::cerr << "Error: no rate available for date." << std::endl;
			continue;
		}
		std::cout << date << " => " << value << " = " << (value * rate) << std::endl;
	}
}