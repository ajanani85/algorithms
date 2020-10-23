#include <iostream>
#include <stdio.h>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <string>
using namespace std;

void stringTo2DArray(const std::string &map, int ***arr, int row, int col);
void create(int ***arr, int row, int col, int default_value);
void print(int **arr, int row, int col);
void pathfinder(int **arr, int row, int col, int start, int end);
void findPaths(int **arr, int row, int col, int start_r, int start_c, int end, std::vector<int> &path);

void findPaths(int **arr, int row, int col, int start_r, int start_c, int end, std::vector<int> &path)
{
	if(start_r*col + start_c == end)
	{
		return;
	}

	if(arr[std::min(start_r+1, row -1 )][start_c] == 1)
	{
		int idx = std::min(start_r+1, row -1)*col + (start_c);
		if(idx == end)
		{
			path.push_back(idx);
			return;
		}

		path.push_back(idx);
		findPaths(arr, row, col, std::min(start_r+1, row -1), start_c, end, path);
	}
	if(arr[start_r][std::min(start_c+1, col-1)] == 1)
	{
		int idx = start_r*col + (std::min(start_c+1, col-1));
		if(idx == end)
		{
			path.push_back(idx);
			return;
		}

		path.push_back(idx);
		findPaths(arr, row, col, start_r, std::min(start_c+1, col-1), end, path);
	}
}

void pathfinder(int **arr, int row, int col, int start, int end)
{
	if(arr == NULL)
	{
		cout << "no path is found" << endl;
	}
	std::vector<std::vector<int>> paths;
	std::vector<int> path;
	path.push_back(start);
	findPaths(arr, row, col, start/col, start%col, end, path);

	for_each(path.begin(), path.end(), [&](int x){cout << x << " ";});
	cout << endl;

}

void stringTo2DArray(const std::string &map, int ***arr, int row, int col)
{
	if((*arr) == NULL)
	{
		create(arr, row, col, 0);
	}

	int length = map.size();
	for(int i = 0; i < map.length(); i++)
	{
		int val = map[i] - '0';

		int r = i / col;
		int c = i % col;
		(*arr)[r][c] = val;
	}
	cout << endl;
}

void create(int ***arr, int row, int col, int default_value)
{
	(*arr) = new int*[row];
	for(int i = 0; i < row; i++)
	{
		(*arr)[i] = new int[col];
	}

	for(int r = 0; r < row; r++)
	{
		for(int c = 0; c < col; c++)
		{
			(*arr)[r][c] = default_value;
		}
	}
}

void print(int **arr, int row, int col)
{
	if(arr == NULL)
	{
		return;
	}

	for(int r = 0; r < row; r++)
	{
		for(int c = 0; c < col; c++)
		{
			cout << arr[r][c] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void printArr2d(const std::vector<std::vector<int>> &src)
{

	for(const std::vector<int> &a : src)
	{
		cout << "{";
		for_each(a.begin(), a.end(), [&](int x){cout << x << " ";});
		cout << "}" <<endl;
	}
}

void cluster(const std::vector<std::vector<int>> &src, std::vector<std::vector<int>> &res,
		int kernel_type = 1)
{
	printArr2d(src);

	int rows = src.size();
	int cols = src[0].size();

	//form the clusters
	std::vector<std::unordered_set<int>> raw_clusters;

	for(int r = 0; r < rows; r++)
	{
		for(int c = 0; c < cols; c++)
		{
			//skip if zero
			if(!src[r][c])
			{
				continue;
			}
			std::unordered_set<int> cluster;

			//set kernel boundaries
			/* 3x3 kernel
			 * 1 1 1
			 * 1 1 1
			 * 1 1 1
			 *
			 * 3x3 cross kernel
			 * 0 1 0
			 * 1 1 1
			 * 0 1 0
			 */
			if(kernel_type == 0)
			{
				int r_lbound = std::max(0, r-1);
				int r_hbound = std::min(rows-1, r+1);
				int c_lbound = std::max(0, c-1);
				int c_hbound = std::min(cols-1, c+1);
				for(int i = r_lbound; i <= r_hbound; i++)
				{
					for(int j = c_lbound; j <= c_hbound; j++)
					{
						//skip if zero
						if(!src[i][j])
						{
							continue;
						}
						cluster.insert(cols*i + j);
					}
				}
			}
			if(kernel_type == 1)
			{
				if(src[std::max(r-1, 0)][c])
				{
					cluster.insert(cols*std::max(r-1, 0) + c);
				}
				if(src[std::min(r+1, rows - 1)][c])
				{
					cluster.insert(cols*std::min(r+1, rows-1) + c);
				}
				if(src[r][std::max(c-1, 0)])
				{
					cluster.insert(cols*r + std::max(c-1, 0));
				}
				if(src[r][std::min(c+1, cols - 1)])
				{
					cluster.insert(cols*r + std::min(c+1, cols-1));
				}
				cluster.insert(cols*r + c);
			}

			raw_clusters.push_back(cluster);

		}
	}

	//iterate through the clusters
	for(int i = 0; i < raw_clusters.size(); i++)
	{
		if(raw_clusters[i].size() == 0)
		{
			continue;
		}
		for(int j = 0; j < raw_clusters.size(); j++)
		{
			if(raw_clusters[j].size() == 0 || i == j)
			{
				continue;
			}

			//check if they are mergeable
			bool mergeable = false;
			std::unordered_set<int>::iterator it_set = raw_clusters[i].begin();
			for(; it_set != raw_clusters[i].end(); ++it_set)
			{
				if(raw_clusters[j].find(*it_set) != raw_clusters[j].end())
				{
					mergeable = true;
					break;
				}
			}

			//actual merge
			if(mergeable)
			{
				raw_clusters[i].insert(raw_clusters[j].begin(), raw_clusters[j].end());
				raw_clusters[j].clear();
			}

		}
	}

	int label = 0;
	for(int i = 0; i < raw_clusters.size(); i++)
	{
		if(raw_clusters[i].size() == 0)
		{
			continue;
		}



		label++;

		for(std::unordered_set<int>::iterator it = raw_clusters[i].begin(); it != raw_clusters[i].end(); ++it)
		{
			res[*it / cols][*it % cols] = label;
		}


		//cout << "cluster at label " << label << ": ";
		//for_each(raw_clusters[i].begin(), raw_clusters[i].end(), [&](int x){cout << x << " ";});
		//cout << endl;
	}
	printArr2d(res);
}


int main(int argc, char **argv) {
	int **arr = NULL;
	int row = 4, col = 4, default_val = 0;

	/*std::vector<std::vector<int>> arr = {{1, 1, 0, 0, 1, 0, 0, 1},
										 {1, 1, 0, 0, 1, 0, 0, 1},
										 {0, 0, 0, 0, 1, 1, 1, 1},
										 {0, 1, 0, 1, 0, 0, 0, 0}};
	std::vector<std::vector<int>> arr_labeled;
	arr_labeled.resize(arr.size());
	for(std::vector<int> &a : arr_labeled)
	{
		a.resize(arr[0].size());
	}

	cluster(arr, arr_labeled);*/
	create(&arr, row, col, default_val);

	std::string map_str="1000100010001111";

	stringTo2DArray(map_str, &arr, row, col);

	pathfinder(arr, row, col, 0, (row*col)-1);

	print(arr, row, col);

	return 0;
}
