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
#include <sstream>
#include <assert.h>
#include <iostream>

namespace Day07
{
	void iterTachA(char** grid, int rows, int cols, int i, int j, int& split)
	{
		if (i == rows){
			return;
		}

		if (grid[i][j] == '.')
		{
			grid[i][j] = '|';
			iterTachA(grid, rows, cols, i+1, j, split);
		}
		else if (grid[i][j] == '^')
		{
			++split;
			if (j > 0){
				iterTachA(grid, rows, cols, i+1, j-1, split);
			}

			if (j < cols - 1)
			{
				iterTachA(grid, rows, cols, i+1, j+1, split);
			}
		}
		else if (grid[i][j] == '|'){
			// neighbour already set it, ignore
		}
	}

	std::string PartA(const StringVector& input)
	{
		const int rows = input.size();
		const int cols = input[0].size();
		int si, sj;

		char** grid = common::CreateGrid<char>(rows, cols);

		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < rows; ++j)
			{
				grid[i][j] = input[i][j];
				if (grid[i][j] == 'S'){
					si = i;
					sj = j;
				}
			}
		}
		int split = 0;
		iterTachA(grid, rows, cols, si + 1, sj, split);

		common::DeleteGrid(grid, rows, cols);

		return std::to_string(split);
	}

	void PrintGrid(char** grid, int rows, int cols)
	{
		system("clear");
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < rows; ++j)
			{
				std::cout << grid[i][j];
			}
			std::cout << std::endl;
		}
	}

	struct Block{
		IntPair pos;
		int64_t val;
	};

	Block* GetBlockByPos(std::vector<Block>& blocks, IntPair pos)
	{
		for (Block& block : blocks)
		{
			if (block.pos == pos)
			{
				return &block;
			}
		}

		return nullptr;
	}

	void iterTachB(char** grid, int rows, int cols, int i, std::vector<Block>& blocks)
	{
		++i;
		if (i == rows){
			return;
		}

		for (Block& block : blocks)
		{
			block.pos.first = i;
		}

		// process every block
		int blockCount = blocks.size();
		for (int k = 0; k < blockCount; ++k)
		{
			Block& block = blocks[k];
			int j = block.pos.second;

			if (grid[i][j] == '^')	// split block
			{
				// spawn blocks
				if (j > 0){
					// left
					// check if a block already exists on the left
					if (Block* left = GetBlockByPos(blocks, std::make_pair(block.pos.first, (block.pos.second - 1))))
					{
						left->val += block.val;
					}
					else
					{
						// spawn a block on the left side
						blocks.push_back({std::make_pair(block.pos.first, block.pos.second - 1), block.val});
					}
				}

				if (j < cols - 1)
				{
					// check if a block already exists on the right
					if (Block* right = GetBlockByPos(blocks, std::make_pair(block.pos.first, (block.pos.second + 1))))
					{
						right->val += block.val;
					}
					else
					{
						// spawn a block on the right side
						blocks.push_back({std::make_pair(block.pos.first, block.pos.second + 1), block.val});
					}
				}

				// set current block to be destroyed
				block.val = 0;
			}
		}

		// removed outdated blocks
		blocks.erase(
			std::remove_if(blocks.begin(), blocks.end(),
				[](const Block& element){
					return element.val == 0;
				}), blocks.end()
		);

		iterTachB(grid, rows, cols, i, blocks);
	}

	std::string PartB(const StringVector& input)
	{
		const int rows = input.size();
		const int cols = input[0].size();
		int si, sj;
		uint64_t result = 0;

		char** grid = common::CreateGrid<char>(rows, cols);

		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < rows; ++j)
			{
				grid[i][j] = input[i][j];
				if (grid[i][j] == 'S'){
					si = i;
					sj = j;
				}
			}
		}

		std::vector<Block> blocks;
		blocks.reserve(1000000);
		blocks.push_back({std::make_pair(si, sj), 1});
		iterTachB(grid, rows, cols, si, blocks);

		for (const Block& block : blocks)
		{
			result+=block.val;
		}

		common::DeleteGrid(grid, rows, cols);

		return std::to_string(result);
	}

	std::pair<std::string, std::string> RunDay(const std::filesystem::path& inputFile)
	{
		StringVector input;
		common::ReadEntireFileStrings(inputFile, input);
		return std::make_pair(PartA(input), PartB(input));
	}
}
