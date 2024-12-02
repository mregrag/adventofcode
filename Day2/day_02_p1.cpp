/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day_02_p1.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:09:42 by mregrag           #+#    #+#             */
/*   Updated: 2024/12/02 16:19:57 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstddef>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
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

std::vector<int> parseLine(const std::string& line)
{
	std::vector<int> levels;
	std::istringstream iss(line);
	int number;
	while (iss >> number)
		levels.push_back(number);
	return (levels);
}

bool isSafeReport(const std::vector<int>levels)
{
	bool is_increasing;
	bool is_decreasing;
	int diff;
	if (levels.size() < 2)
		return (true);

	is_increasing = true;
	is_decreasing = true;

	for(size_t i = 1; i < levels.size(); ++i)
	{
		diff = levels[i] - levels[i - 1];
		if (std::abs(diff) < 1 || std::abs(diff) > 3)
			return (false);
		if (diff > 0)
			is_decreasing = false;
		else if (diff < 0)
			is_increasing = false;
	}
	return (is_increasing || is_decreasing);
}

int numbrreportsafe(const std::string& filecontent)
{
	std::istringstream iss(filecontent);
	std::string line;
	std::vector<int>levels;
	int safeCount = 0;

	while (std::getline(iss, line))
	{
		levels = parseLine(line);
		if (isSafeReport(levels))
			++safeCount;
	}
	return (safeCount);
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
	int reportSafe = numbrreportsafe(fileContent);
	std::cout << reportSafe << std::endl;

	return (0);
}
