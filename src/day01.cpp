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

namespace Day01
{
	std::string PartA(const StringVector& input)
	{
		int dial = 50;
		int zeroClicks = 0;
		for(const std::string& line : input)
		{
			const char dir = line.at(0);
			int amount = std::stoi(line.substr(1, line.length() - 1));

			if (dir == 'L')
			{
				amount %= 100;
				int result = dial - amount;
				if (result < 0){
					dial = 99 - (0 - result - 1);
				}else{
					dial = result;
				}
			}
			else
			{
				amount %= 100;
				int result = dial + amount;
				if (result > 99){
					dial = 0 + (result - 99 - 1);
				}else{
					dial = result;
				}
			}

			if (dial == 0){
				++zeroClicks;
			}
		}
		return std::to_string(zeroClicks);
	}

	std::string PartB(const StringVector& input)
	{
		int dial = 50;
		int zeroClicks = 0;

		for(const std::string& line : input)
		{
			const int dir = (line.at(0) == 'L') ? -1 : 1;
			int amount = std::stoi(line.substr(1, line.length() - 1));

			if (amount > 100){
				zeroClicks += (amount / 100);
				amount %= 100;
			}

			amount *= dir;
			int prevDial = dial;
			dial += amount;

			// edge case
			if (dial == 100){
				dial = 0;
			}

			if (dial > 100){
				zeroClicks += (dial / 100);
				dial %= 100;
			}else if (dial < 0){
				int wraps = (std::abs(dial) + 99) / 100;
				if (prevDial > 0){
					zeroClicks += wraps;
				}
				dial += wraps * 100;
			}

			// did it land on a zero?
			if (dial == 0){
				++zeroClicks;
			}
		}
		return std::to_string(zeroClicks);
	}

	std::pair<std::string, std::string> RunDay(const std::filesystem::path& inputFile)
	{
		StringVector input;
		common::ReadEntireFileStrings(inputFile, input);
		return std::make_pair(PartA(input), PartB(input));
	}
}
