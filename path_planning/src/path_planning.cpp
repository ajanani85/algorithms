#include <iostream>
#include "path_planning_DFS.h"
#include <memory>

std::shared_ptr<PathPlanningDFS> path_planner_;

int main(int argc, char **argv)
{
	path_planner_ = std::make_shared<PathPlanningDFS>();
	if(path_planner_->loadData("test/test_data_1.txt") < 0)
	{
		std::cerr << "error reading file" << std::endl;
		return -1;
	}

	path_planner_->print("");

	std::vector<std::queue<int>> paths;
	path_planner_->getAllPaths(paths);
	return 0;
}
