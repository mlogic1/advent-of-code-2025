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

#include <days.h>
#include <iostream>
#include <assert.h>
#include <unordered_map>

std::unordered_map<int, std::pair<std::string, std::string>(*)(const std::filesystem::path&)> all_days =
{
	{ 1, Day01::RunDay }
};

int main(int argc, const char* argv[])
{
	assert(argc == 3);
	int dayNr = std::stoi(argv[1]);
	std::filesystem::path inputFile = argv[2];

	assert (dayNr >= 1 && dayNr <= 12);
	assert (!std::filesystem::exists(inputFile));

	auto result = all_days.at(dayNr)(inputFile);
	std::cout << "Day " << dayNr << std::endl << "A: " << result.first << std::endl << "B: " << result.second << std::endl;
	return 0;
}
