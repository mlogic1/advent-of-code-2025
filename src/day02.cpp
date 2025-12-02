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

namespace Day02
{
	std::vector<StringPair> LoadIDs(const std::string& input)
	{
		std::vector<StringPair> result;
		StringVector ranges = common::SplitStringWithDelimiter(input, ',');
		for (const std::string& range : ranges)
		{
			StringVector r = common::SplitStringWithDelimiter(range, '-');
			result.push_back(std::make_pair(r[0], r[1]));
		}
		
		return result;
	}

	inline bool idValidA(const std::string& id)
	{
		if (id.length() % 2 != 0){
			return true;
		}
		std::string halfId = id.substr(0, id.length() / 2);
		return (halfId + halfId != id);
	}

	inline bool idValidB(const std::string& id)
	{
		std::string doubleId = id + id;
		doubleId = doubleId.substr(1, doubleId.length() - 2);
		if (doubleId.find(id) != std::string::npos){
			return false;
		}
		return true;
	}

	std::string PartA(const std::vector<StringPair>& input)
	{
		uint64_t invalidSum = 0;
		for (const StringPair& idPair: input)
		{
			uint64_t A = std::stoull(idPair.first), B = std::stoull(idPair.second);
			
			for (uint64_t i = A; i <= B; ++i){
				if (!idValidA(std::to_string(i))){
					invalidSum += i;
				}
			}
		}
		return std::string(std::to_string(invalidSum));
	}

	std::string PartB(const std::vector<StringPair>& input)
	{
		uint64_t invalidSum = 0;
		for (const StringPair& idPair: input)
		{
			uint64_t A = std::stoull(idPair.first), B = std::stoull(idPair.second);
			
			for (uint64_t i = A; i <= B; ++i){
				if (!idValidB(std::to_string(i))){
					std::cout << i << std::endl;
					invalidSum += i;
				}
			}
		}
		return std::string(std::to_string(invalidSum));
	}

	std::pair<std::string, std::string> RunDay(const std::filesystem::path& inputFile)
	{
		StringVector input;
		common::ReadEntireFileStrings(inputFile, input);
		std::vector<StringPair> IDs = LoadIDs(input[0]);
		return std::make_pair(PartA(IDs), PartB(IDs));
	}
}
