#include <iostream>
#include <memory>
#include "path_planning_BFS.h"

std::shared_ptr<PathPlanningBFS> path_planner_;

int main(int argc, char **argv)
{
	path_planner_ = std::make_shared<PathPlanningBFS>();
	if(path_planner_->loadData("test/test_data_1.txt") < 0)
	{
		std::cerr << "error reading file" << std::endl;
		return -1;
	}

	path_planner_->print("");

	std::vector<std::vector<int>> paths;
	path_planner_->getAllPaths(paths, 0, path_planner_->grid_.size() - 1);
	path_planner_->print(paths);
	return 0;
}
