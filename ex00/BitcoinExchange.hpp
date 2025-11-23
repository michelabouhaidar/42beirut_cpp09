/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 16:48:55 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/11/23 22:26:10 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

class BitcoinExchange
{
	private:
		std::map<std::string, double> rates_;
		std::string trim(const std::string& s)const;
		bool isValidDateFormat(const std::string& date) const;
		bool isValidDate(const std::string& date) const;
		bool parseValue(const std::string& str, double& value) const;
		bool getRateForDate(const std::string& date, double &rate) const;
	public:
		BitcoinExchange();
		BitcoinExchange(const std::string& dbFile);
		BitcoinExchange(const BitcoinExchange& obj);
		BitcoinExchange& operator=(const BitcoinExchange& obj);
		~BitcoinExchange();
		void localDatabase(const std::string &dbFile);
		void processInput(const std::string &inputFile) const;
};

#endif