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

namespace Day04
{
	int neighbourCount(char** grid, int rows, int cols, int i, int j)
	{
		int neighbours = 0;
		if (j > 0){
			// check left
			if (grid[i][j-1] == '@')
				++neighbours;

			if (i > 0){
				// check top left
				if (grid[i-1][j-1] == '@')
					++neighbours;
			}

			if (i < rows - 1){
				// check bottom left
				if (grid[i+1][j-1] == '@')
					++neighbours;
			}
		}

		if (i > 0){
			// check top
			if (grid[i-1][j] == '@')
				++neighbours;
		}

		if (j < cols - 1){
			// check right
			if (grid[i][j+1] == '@')
				++neighbours;

			if (i < rows - 1){
				// check bottom right
				if (grid[i+1][j+1] == '@')
					++neighbours;
			}

			if (i > 0){
				// check top right
				if (grid[i - 1][j+1] == '@')
					++neighbours;
			}
		}

		if (i < rows - 1){
			// check bottom
			if (grid[i+1][j] == '@')
				++neighbours;
		}

		return neighbours;
	}

	std::string PartA(char** grid, int rows, int cols)
	{
		int result = 0;

		for (int i = 0; i < rows; ++i){
			for (int j = 0; j < cols; ++j){
				if (grid[i][j] != '@')
					continue;
				

				int neighbours = neighbourCount(grid, rows, cols, i, j);
				if (neighbours < 4){
					++result;
				}
			}
		}

		return std::to_string(result);
	}

	char** CopyGrid(char** grid, int rows, int cols)
	{
		char** newGrid = common::CreateGrid<char>(rows, cols);

		for (int i = 0; i < rows; ++i){
			for (int j = 0; j < cols; ++j){
				newGrid[i][j] = grid[i][j];
			}
		}

		return newGrid;
	}

	std::string PartB(char** grid, int rows, int cols)
	{
		uint64_t result = 0;
		char** currentGrid = CopyGrid(grid, rows, cols);
		char** tmpGrid = CopyGrid(grid, rows, cols);

		int removedPieces = 0;
		do{
			removedPieces = 0;
			for (int i = 0; i < rows; ++i){
				for (int j = 0; j < cols; ++j){
					tmpGrid[i][j] = currentGrid[i][j];
					if (currentGrid[i][j] != '@')
						continue;
					
					int neighbours = neighbourCount(currentGrid, rows, cols, i, j);
					if (neighbours < 4){
						tmpGrid[i][j] = 'x';
						++removedPieces;
						++result;
					}
				}
			}

			for (int i = 0; i < rows; ++i){
				for (int j = 0; j < cols; ++j){
					currentGrid[i][j] = tmpGrid[i][j];
				}
			}			
		}while(removedPieces > 0);


		common::DeleteGrid(tmpGrid, rows, cols);
		common::DeleteGrid(currentGrid, rows, cols);

		return std::to_string(result);
	}

	std::pair<std::string, std::string> RunDay(const std::filesystem::path& inputFile)
	{
		StringVector input;
		common::ReadEntireFileStrings(inputFile, input);

		const int rows = input.size();
		const int cols = input[0].length();
		char** grid = common::CreateGrid<char>(rows, cols);

		for (int i = 0; i < rows; ++i){
			for (int j = 0; j < rows; ++j){
				grid[i][j] = input[i].at(j);
			}
		}

		auto result = std::make_pair(PartA(grid, rows, cols), PartB(grid, rows, cols));
		common::DeleteGrid(grid, rows, cols);
		return result;
	}
}