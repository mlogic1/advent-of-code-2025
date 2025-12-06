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
#include <sstream>
#include <assert.h>
#include <iostream>

namespace Day06
{
	std::string PartA(const StringVector& input)
	{
		std::vector<std::vector<int64_t>> numGrid;
		std::vector<char> operations;
		for (int i = 0; i < input.size() - 1;++i)
		{
			std::vector<int64_t> numLine;
			std::stringstream ss(input[i]);
			int64_t tmp;
			while(ss >> tmp)
			{
				numLine.push_back(tmp);
			}
			numGrid.push_back(std::move(numLine));
		}

		std::stringstream ss(input.back());
		char tmp;
		while(ss >> tmp)
		{
			operations.push_back(tmp);
		}

		const size_t size = numGrid[0].size();
		assert(size == operations.size());

		uint64_t total = 0;

		for (int j = 0; j < size; ++j)
		{
			char op = operations[j];
			uint64_t colResult = (op == '*') ? 1 : 0;
			for (int i = 0; i < numGrid.size(); ++i)
			{
				int64_t num = numGrid[i][j];
				if (op == '*'){
					colResult *= num;
				}else{
					colResult += num;
				}
			}
			total += colResult;
		}
		
		return std::to_string(total);
	}

	std::string PartB(const StringVector& input)
	{
		StringVector result;
		IntVector splitIndexes;

		std::string opsStr = input.back();
		for (int i = 1; i < opsStr.size(); ++i)
		{
			if (opsStr[i] != ' ')
			{
				splitIndexes.push_back(i - 1);
			}
		}

		splitIndexes.push_back(opsStr.size());

		const size_t rows = input.size();

		for (int i = 0; i < rows - 1; ++i)
		{
			result.push_back("");
		}

		uint64_t totalResult = 0;

		int prevIndex = 0;
		for (int index : splitIndexes)
		{
			IntVector nums;
			for (int i = 0; i < rows - 1; ++i)
			{
				size_t len = index - prevIndex;
				result[i] += input[i].substr(prevIndex, len);
			}

			// read the numbers top to bottom
			char operation = opsStr[prevIndex];
			uint64_t colResult = (operation == '*') ? 1 : 0;
			for (int j = result[0].size() - 1; j >= 0; --j)
			{
				std::string col = "";
				for (int i = 0; i < rows - 1; ++i)
				{
					col += result[i][j];
				}

				int64_t num = std::stoll(col);
				if (operation == '*'){
					colResult *= num;
				}else{
					colResult += num;
				}
			}			

			totalResult += colResult;
			prevIndex = index + 1;

			for(string& str : result)
			{
				str = "";
			}
		}


		return std::to_string(totalResult);
	}

	std::pair<std::string, std::string> RunDay(const std::filesystem::path& inputFile)
	{
		StringVector input;
		common::ReadEntireFileStrings(inputFile, input);
		return std::make_pair(PartA(input), PartB(input));
	}
}
