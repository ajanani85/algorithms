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

	int size();

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

	int loadData(const std::string &file_location);

	void print(const std::string &msg);

	void print(std::vector<std::vector<int>> &paths);

	void toString(std::vector<int> &path, std::string &str);

	Grid grid_;

	virtual void getAllPaths(std::vector<std::vector<int>> &paths, int start, int end) = 0;

	std::pair<int,int> getBoundaries(int idx, int &row_low, int &row_high, int &col_low, int &col_high);

protected:

private:
};


#endif /* INCLUDE_PATH_PLANNING_BASE_H_ */
