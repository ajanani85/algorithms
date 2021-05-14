#include <iostream>
#include "path_planning_DFS.h"
#include <memory>

std::shared_ptr<PathPlanningDFS> path_planner_;

int main(int argc, char **argv)
{
	path_planner_ = std::make_shared<PathPlanningDFS>();
	return 0;
}
