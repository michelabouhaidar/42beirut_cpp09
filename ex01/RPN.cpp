/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 02:52:13 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/11/24 03:19:20 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <sstream>
#include <stdexcept>
#include <cctype>


RPN::RPN() {}

static bool isOperator(char c)
{
	return (c == '+' || c == '-' || c == '/' || c == '*');
}

static int applyOperator(int left, int right, char op)
{
	switch (op)
	{
		case '+':
			return left + right;
		case '-':
			return left - right;
		case '*':
			return left * right;
		case '/':
			if (right == 0)
				throw std::runtime_error("division by zero");
			return left / right;
		default:
			throw std::runtime_error("invalid operator");
	}
}

int RPN::evaluate(const std::string& exp)
{
	while (!stack_.empty())
		stack_.pop();

	std::istringstream iss(exp);
	std::string token;

	while (iss >> token)
	{
		if (token.size() == 1 && std::isdigit(static_cast<unsigned char>(token[0])))
		{
			int value = token[0] - '0';
			stack_.push(value);
		}
		else if (token.size() == 1 && isOperator(token[0]))
		{
			if (stack_.size() < 2)
				throw std::runtime_error("not enough operands");
			int right = stack_.top();
			stack_.pop();
			int left = stack_.top();
			stack_.pop();
			int result = applyOperator(left, right, token[0]);
			stack_.push(result);
		}
		else
			throw std::runtime_error("invalid token");
	}
	if (stack_.size() != 1)
		throw std::runtime_error("malformed expression");
	return stack_.top();
}
