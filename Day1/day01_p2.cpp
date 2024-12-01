/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day01_p2.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 17:02:54 by mregrag           #+#    #+#             */
/*   Updated: 2024/12/01 17:13:04 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
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

int calculateSimilarityScore(const std::string& fileContent)
{
	std::istringstream iss(fileContent);

	std::vector<int> leftCol;
	std::map<int, int> rightColcount;
	int left;
	int right;

	while (iss >> left >> right)
	{
		leftCol.push_back(left);
		rightColcount[right]++;
	}


	int similarityScore = 0;
	for (size_t i = 0; i < leftCol.size(); ++i)
	{
		int count = rightColcount[leftCol[i]];
		similarityScore += leftCol[i] * count;
	}

	return (similarityScore);
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

	int similarityScore = calculateSimilarityScore(fileContent);

	std::cout << "Total Distance: " << similarityScore << std::endl;

	return (0);
}
