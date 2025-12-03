/************************  ADVENT OF CODE 2025 **********************************
**                         adventofcode.com                                     *       *
**                                                                              *      /.\
**                         mlogic1 (https://github.com/mlogic1)                 *     /..'\
**                                                                              *     /'.'\
**                                                                              *    /.''.'\
**                                                                              *    /.'.'.\
**                                                                              *   /'.''.'.\
**                                                                              *   ^^^[_]^^^
********************************************************************************/

#include <string>
#include <filesystem>
#include "advent-common.h"
#include <iostream>
#include <set>

namespace Day03
{
	std::string PartA(const StringVector& input)
	{
		uint64_t sum = 0;
		
		for (const std::string& line : input)
		{
			std::vector<uint32_t> nums;
			for(char c : line)
			{
				nums.push_back(c - '0');
			}

			uint32_t greatest = 0;
			const int size = nums.size();
			
			for (int i = 0; i < size; ++i){
				for (int j = i; j < size; ++j){
					if (i == j){
						continue;
					}
					int total = (nums[i] * 10) + nums[j];
					if (total > greatest){
						greatest = total;
					}
				}
			}
			sum += greatest;
		}

		return std::string(std::to_string(sum));
	}

	uint64_t iterate(const std::vector<uint32_t>& nums, const int index, std::string current = "")
	{
		const int currentDigitNum = current.length();
		if (currentDigitNum == 12){
			return std::stoull(current);
		}
		
		const int mi = nums.size() - (12 - currentDigitNum);

		int largestDigit = 0;
		int largestDigitIndex = 0;

		for (int i = index; i <= mi; ++i){
			if (nums[i] > largestDigit){
				largestDigit = nums[i];
				largestDigitIndex = i;
			}
		}
		current += std::to_string(largestDigit);

		return iterate(nums, largestDigitIndex + 1, current);
	}

	std::string PartB(const StringVector& input)
	{
		uint64_t sum = 0;
		
		for (const std::string& line : input)
		{
			std::vector<uint32_t> nums;
			for(char c : line)
			{
				nums.push_back(c - '0');
			}

			uint64_t result = iterate(nums, 0);
			sum += result;
		}

		return std::string(std::to_string(sum));
	}

	std::pair<std::string, std::string> RunDay(const std::filesystem::path& inputFile)
	{
		StringVector input;
		common::ReadEntireFileStrings(inputFile, input);
		return std::make_pair(PartA(input), PartB(input));
	}
}