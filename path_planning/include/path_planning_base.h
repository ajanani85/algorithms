/*
 * path_planning.h
 *
 *  Created on: May 13, 2021
 *      Author: amros
 */

#ifndef INCLUDE_PATH_PLANNING_BASE_H_
#define INCLUDE_PATH_PLANNING_BASE_H_

#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <stack>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
struct Grid
{
	Grid(int row, int col);

	Grid();

	void setup(int row, int col);

	int getGlobalIndex(int r, int c);

	std::pair<int,int> getRowCol(int g_idx);

	void asString(std::string &data);

	std::vector<int> data_;

	int rows;

	int cols;
};

class PathPlanningBase
{
public:

	PathPlanningBase();

	virtual ~PathPlanningBase() = 0;

protected:

	int loadData(const std::string &file_location);

	void print(const std::string &msg);

	Grid grid_;

private:
};


#endif /* INCLUDE_PATH_PLANNING_BASE_H_ */
