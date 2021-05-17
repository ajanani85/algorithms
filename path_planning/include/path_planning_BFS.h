/*
 * path_planning_DFS.h
 *
 *  Created on: May 13, 2021
 *      Author: amros
 */

#ifndef INCLUDE_PATH_PLANNING_BFS_H_
#define INCLUDE_PATH_PLANNING_BFS_H_

#include "path_planning_base.h"

class PathPlanningBFS : public PathPlanningBase
{
public:
	PathPlanningBFS();

	~PathPlanningBFS();

	void getAllPaths(std::vector<std::vector<int>> &paths, int start, int end);

private:

	void bfs(std::vector<int> &path, std::unordered_set<int> &visited, int idx, int end);
};


#endif /* INCLUDE_PATH_PLANNING_BFS_H_ */
