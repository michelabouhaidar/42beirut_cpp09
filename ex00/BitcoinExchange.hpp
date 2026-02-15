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
	public:
		BitcoinExchange();
		BitcoinExchange(const std::string& dbFile);
		void localDatabase(const std::string &dbFile);
		void processInput(const std::string &inputFile) const;
};

#endif