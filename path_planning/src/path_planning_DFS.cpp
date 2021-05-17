/*
 * path_planning_DFS.cpp
 *
 *  Created on: May 13, 2021
 *      Author: amros
 */

#include "path_planning_DFS.h"

PathPlanningDFS::PathPlanningDFS()
{
}

PathPlanningDFS::~PathPlanningDFS()
{
}

void PathPlanningDFS::getAllPaths(std::vector<std::queue<int>> &paths, int start, int end)
{
	//todo: check for start and end in boundaries
	if(grid_.size() == 0 || grid_.data_[start] == 0 || grid_.data_[end] == 0)
	{
		return;
	}

	if(start > end)
	{
		std::swap(start, end);
	}

	//find the boundaries
	auto start_cell = grid_.getRowCol(start);
	int r_hb = std::min(start_cell.first + 1, grid_.rows - 1);
	int r_lb = std::max(start_cell.first - 1, 0);
	int c_hb = std::min(start_cell.second + 1, grid_.cols - 1);
	int c_lb = std::max(start_cell.second - 1, 0);

	for(int r = r_lb; r <= r_hb; r++)
	{
		for(int c = c_lb; c <= c_hb; c++)
		{
			int idx = grid_.getGlobalIndex(r, c);
			if(grid_.data_[idx] == 0)
			{
				continue;
			}
			//create a path
			std::queue<int> path;
			path.push(start);

			//create a visited list
			std::unordered_set<int> visited;
			visited.insert(start);

			int result = dfs(path, visited, idx);

			if(result > 0)
			{
				paths.push_back(path);
			}
		}
	}
}

int PathPlanningDFS::dfs(std::queue<int> &path, std::unordered_set<int> &visited, int idx)
{
}
