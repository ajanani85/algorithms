/*
 * path_planning_DFS.cpp
 *
 *  Created on: May 13, 2021
 *      Author: amros
 */

#include "path_planning_BFS.h"

PathPlanningBFS::PathPlanningBFS()
{
}

PathPlanningBFS::~PathPlanningBFS()
{
}

void PathPlanningBFS::getAllPaths(std::vector<std::vector<int>> &paths, int start, int end)
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

	int r_lb = 0;
	int r_hb = 0;
	int c_lb = 0;
	int c_hb = 0;
	auto start_cell = getBoundaries(start, r_lb, r_hb, c_lb, c_hb);

	std::queue<int> list;
	list.push(start);


	bfs(path, visited, start, end);

}

void PathPlanningBFS::bfs(std::vector<int> &path, std::unordered_set<int> &visited, int idx, int end)
{
	//already visited
	if(visited.find(idx) != visited.end() || grid_.data_[idx] == 0)
	{
		return;
	}

	//destination is reached
	if(idx == end)
	{
		path.push_back(idx);
		return;
	}

	visited.insert(idx);
	path.push_back(idx);

	int r_l = 0;
	int r_h = 0;
	int c_l = 0;
	int c_h = 0;
	auto cell = getBoundaries(idx, r_l, r_h, c_l, c_h);

	for(int r = r_l; r <= r_h; r++)
	{
		for(int c = c_l; c <= c_h; c++)
		{
			bfs(path, visited, grid_.getGlobalIndex(r,c),end);
			if(visited.find(end) != visited.end())
			{
				path.push_back(idx);
			}
		}
	}


}
