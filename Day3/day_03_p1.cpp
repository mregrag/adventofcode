/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day_03_p1.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:36:00 by mregrag           #+#    #+#             */
/*   Updated: 2024/12/03 18:31:06 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <sstream>

std::string readFile(const std::string& filename)
{
	std::ifstream file(filename.c_str());
	if (!file.is_open())
	{
		std::cout << "Error opening file: " << filename << std::endl;
		return "";
	}
	std::stringstream buffer;
	buffer << file.rdbuf();
	return (buffer.str());
}

int calculateSumOfMultiplications(const std::string& fileContent)
{
	std::regex mulPattern("mul\\((\\d{1,3}),(\\d{1,3})\\)");
	std::smatch match;
	std::string::const_iterator searchStart(fileContent.cbegin());
	int totalSum = 0;

	while (std::regex_search(searchStart, fileContent.cend(), match, mulPattern))
	{
		int x = std::stoi(match[1].str());
		int y = std::stoi(match[2].str());
		totalSum += x * y;

		searchStart = match.suffix().first;
	}
	return (totalSum);
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
		return (1);
	}

	std::string fileContent = readFile(argv[1]);
	if (fileContent.empty())
		return (1);

	int result = calculateSumOfMultiplications(fileContent);
	std::cout << "Total Sum: " << result << std::endl;

	return (0);
}

