/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day_03_p2.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 18:40:51 by mregrag           #+#    #+#             */
/*   Updated: 2024/12/03 18:44:29 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <sstream>

std::string readFile(const std::string& filename)
{
	std::ifstream file(filename);
	if (!file.is_open())
	{
		std::cout << "Error opening file: " << filename << std::endl;
		return "";
	}
	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

int calculateConditionalMultiplications(const std::string& fileContent)
{
	std::regex instructionPattern(R"(do\(\)|don't\(\)|mul\((\d{1,3}),(\d{1,3})\))");
	std::smatch match;
	std::string::const_iterator searchStart(fileContent.cbegin());

	bool isEnabled = true; 
	int totalSum = 0;

	while (std::regex_search(searchStart, fileContent.cend(), match, instructionPattern))
	{
		std::string instruction = match[0];

		if (instruction == "do()")
			isEnabled = true;
		else if (instruction == "don't()")
			isEnabled = false;
		else if (match[1].matched && match[2].matched)
		{
			if (isEnabled)
			{
				int x = std::stoi(match[1].str());
				int y = std::stoi(match[2].str());
				totalSum += x * y;
			}
		}
		searchStart = match.suffix().first;
	}
	return (totalSum);
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
		return (1);
	}

	std::string fileContent = readFile(argv[1]);
	if (fileContent.empty())
		return (1);
	int result = calculateConditionalMultiplications(fileContent);
	std::cout << "Sum of enabled multiplications: " << result << std::endl;
	return (0);
}

