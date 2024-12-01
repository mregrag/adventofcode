/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day01_p1.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 15:52:30 by mregrag           #+#    #+#             */
/*   Updated: 2024/12/01 17:40:10 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void bubbleSort(std::vector<int>& v)
{
	int n = v.size();
	bool swapped;

	for (int i = 0; i < n - 1; i++)
	{
		swapped = false;

		for (int j = 0; j < n - i - 1; j++)
		{
			if (v[j] > v[j + 1])
			{
				std::swap(v[j], v[j + 1]);
				swapped = true;
			}
		}
		if (!swapped)
			break;
	}
}

int calculateTotalDistance(const std::string& fileContent)
{
	std::istringstream iss(fileContent);

	std::vector<int> leftCol;
	std::vector<int> rightCol;
	int left;
	int right;

	while (iss >> left >> right)
	{
		leftCol.push_back(left);
		rightCol.push_back(right);
	}

	if (leftCol.size() != rightCol.size()) 
	{
		std::cerr << "Error : columns have different sizes" << std::endl;
		return (-1);
	}

	bubbleSort(leftCol);
	bubbleSort(rightCol);

	int totalDistance = 0;
	for (size_t i = 0; i < leftCol.size(); ++i)
		totalDistance += std::abs(leftCol[i] - rightCol[i]);

	return (totalDistance);
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
		return 1;
	}

	std::string fileContent = readFile(argv[1]);
	if (fileContent.empty())
		return (1);

	int totalDistance = calculateTotalDistance(fileContent);
	if (totalDistance == -1)
		return (1);

	std::cout << "Total Distance: " << totalDistance << std::endl;

	return (0);
}
