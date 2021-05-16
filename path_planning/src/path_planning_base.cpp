/*
 * path_planning_base.cpp
 *
 *  Created on: May 13, 2021
 *      Author: alireza
 */

#include "path_planning_base.h"

Grid::Grid(int row, int col)
{
	setup(row, col);
}

Grid::Grid()
{
	setup(10, 10);
}

void Grid::setup(int row, int col)
{
	rows = row;
	cols = col;
	data_.resize(row*col);
}

int Grid::getGlobalIndex(int r, int c)
{
	return r*cols + c;
}

std::pair<int,int> Grid::getRowCol(int g_idx)
{
	int row = g_idx / cols;
	int col = g_idx % cols;

	return std::make_pair(row, col);
}

void Grid::asString(std::string &data)
{
	if(data_.size() == 0)
	{
		return;
	}

	for(int r = 0; r < rows; r++)
	{
		for(int c = 0; c < cols; c++)
		{
			data+=std::to_string(data_[getGlobalIndex(r, c)]) + " ";
		}
		data+="\n";
	}
}

PathPlanningBase::PathPlanningBase()
{
}

PathPlanningBase::~PathPlanningBase()
{
}

int PathPlanningBase::loadData(const std::string &file_location)
{
	std::ifstream infile(file_location);

	grid_.rows = 0;
	grid_.cols = 0;
	grid_.data_.resize(0);
	bool firstRound = true;
	while (infile)
	{
		std::string line;
		if (!getline( infile, line ))
		{
			break;
		}

		grid_.rows++;

		std::istringstream ss( line );
		while (ss)
		{
			std::string c;
			if (!getline( ss, c, ',' ))
			{
				break;
			}
			if(firstRound)
			{
				grid_.cols++;
			}
			grid_.data_.push_back(std::stoi(c));
		}
		firstRound = false;

	}

	if(grid_.rows != -1 && grid_.cols != -1)
	{
		return 0;
	}
	return -1;
}

void PathPlanningBase::print(const std::string &msg)
{
	printf("%s\n", msg.c_str());
	std::string data_str;
	grid_.asString(data_str);
	printf("%s", data_str.c_str());
}

void PathPlanningBase::getAllPaths(std::vector<std::queue<int>> &paths)
{
	printf("Implement %s \n", __func__);
}
