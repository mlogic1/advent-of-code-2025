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

#include <algorithm>
#include <string>
#include <filesystem>
#include "advent-common.h"
#include <iostream>

namespace Day05
{
	using u64Pair = std::pair<uint64_t, uint64_t>;
	using u64Vector = std::vector<uint64_t>;

	inline bool InRange(uint64_t lower, uint64_t upper, uint64_t value)
	{
		return (value >= lower && value <= upper);
	}

	void LoadIngredients(const StringVector& input, std::vector<u64Pair>& freshIngredients, u64Vector& availableIngredients)
	{
		bool loadingFresh = true;

		for(const std::string& line : input)
		{
			if (line.empty())
			{
				loadingFresh = false;
				continue;
			}

			if (loadingFresh)
			{
				StringVector r = common::SplitStringWithDelimiter(line, '-');
				freshIngredients.push_back(std::make_pair(std::stoull(r[0]), std::stoull(r[1])));
			}
			else
			{
				availableIngredients.push_back(std::stoull(line));
			}
		}
	}

	std::string PartA(std::vector<u64Pair>& freshIngredients, u64Vector& availableIngredients)
	{
		std::set<uint64_t> freshIds;

		for (const uint64_t& availableIngredient : availableIngredients)
		{
			for (const u64Pair& freshRange : freshIngredients)
			{
				if (InRange(freshRange.first, freshRange.second, availableIngredient))
				{
					freshIds.insert(availableIngredient);
					break;
				}
			}
		}

		return std::to_string(freshIds.size());
	}

	std::string PartB(std::vector<u64Pair>& freshIngredients)
	{
		uint64_t total = 0;
		std::set<uint64_t> startStops;
		for (const u64Pair& pair : freshIngredients)
		{
			startStops.insert(pair.first);
			startStops.insert(pair.second + 1);
		}

		std::vector<uint64_t> startStopsV;

		for (uint64_t val : startStops)
		{
			startStopsV.push_back(val);
		}

		for (int i = 0; i < startStopsV.size() - 1; ++i)
		{
			uint64_t first = startStopsV[i];
			uint64_t second = startStopsV[i + 1];
			for (const u64Pair& pair : freshIngredients)
			{
				if ((first >= pair.first && second <= pair.second + 1))
				{
					total += (second - first);
					break;
				}
			}
		}

		return std::to_string(total);
	}

	std::pair<std::string, std::string> RunDay(const std::filesystem::path& inputFile)
	{
		StringVector input;
		common::ReadEntireFileStrings(inputFile, input);

		std::vector<u64Pair> freshIngredients;
		u64Vector availableIngredients;
		LoadIngredients(input, freshIngredients, availableIngredients);

		return std::make_pair(PartA(freshIngredients, availableIngredients), PartB(freshIngredients));
	}
}
