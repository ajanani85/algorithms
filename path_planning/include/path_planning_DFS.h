/*
 * path_planning_DFS.h
 *
 *  Created on: May 13, 2021
 *      Author: amros
 */

#ifndef INCLUDE_PATH_PLANNING_DFS_H_
#define INCLUDE_PATH_PLANNING_DFS_H_

#include "path_planning_base.h"

class PathPlanningDFS : public PathPlanningBase
{
public:
	PathPlanningDFS();

	~PathPlanningDFS();

	void getAllPaths(std::vector<std::vector<int>> &paths, int start, int end);

private:

	void dfs(std::vector<int> &path, std::unordered_set<int> &visited, int idx, int end);
};


#endif /* INCLUDE_PATH_PLANNING_DFS_H_ */
