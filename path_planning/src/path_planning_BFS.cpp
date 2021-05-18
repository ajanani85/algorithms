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

	//a queue for internal storage of the paths
	std::queue<std::vector<int>> q;

	//store the current path
	std::vector<int> path;
	//put the start position into the first path
	path.push_back(start);
	q.push(path);

	//while the queue is not empty
	while(!q.empty())
	{
		//get a copy of the front path
		path = q.front();
		//get rid of the front path in the internal container
		q.pop();

		//get the last element of the current path
		int last = path[path.size() - 1];

		//see if the destination is reached
		if(last == end)
		{
			paths.push_back(path);
		}

		//figure out the connected graph to the last item of the path
		int rl, rh, cl, ch = 0;
		auto last_cell = getBoundaries(last, rl, rh, cl, ch);

		for(int r = rl; r <= rh; r++)
		{
			for(int c = cl; c <= ch; c++)
			{
				int idx = grid_.getGlobalIndex(r, c);
				//skip if the path is blocked
				if(grid_.data_[idx] == 0)
				{
					continue;
				}

				//see if the path already visited this item
				if(!isVisited(path, idx))
				{
					//create a new path
					std::vector<int> new_path(path);
					//add the current index to the path
					new_path.push_back(idx);
					//store the path
					q.push(new_path);
				}
			}
		}
	}
}
bool PathPlanningBFS::isVisited(const std::vector<int> &path, int key)
{
	std::vector<int>::const_iterator it = path.cbegin();
	for(; it != path.cend(); ++it)
	{
		if(*it == key)
		{
			return true;
		}
	}
	return false;
}
