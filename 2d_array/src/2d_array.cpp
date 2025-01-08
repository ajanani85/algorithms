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


void cluster(const vector<vector<int>> &arr, vector<vector<int>> &res)
{
	
}

/*
	You are given an m x n integer matrix matrix with the following two properties:

    Each row is sorted in non-decreasing order.
    The first integer of each row is greater than the last integer of the previous row.

	Given an integer target, return true if target is in matrix or false otherwise.

	You must write a solution in O(log(m * n)) time complexity.
 */

bool find(vector<vector<int>> &arr, int target)
{
	if(arr.size() == 0)
	{
		return false;
	}
	//a sorted 2D array is a sorted 1D array organized in rows and cols
	int rows = arr.size();
	int cols = arr[0].size();

	int left= 0;
	int right = (rows * cols) - 1;

	//perform binary search
	while(left <= right)
	{
		int mid = left + (right - left)/2;

		int row = mid / cols;
		int col = mid % cols;
		if(arr[row][col] == target)
		{
			return true;
		}
		else if (arr[row][col] < target)
		{
			left = mid + 1;
		}
		else
		{
			right = mid - 1;
		}
	}

	return false;
	
}


int main(int argc, char **argv) {
	/*int **arr = NULL;
	int row = 4, col = 4, default_val = 0;*/

	std::vector<std::vector<int>> arr = {{1, 1, 0, 0, 1, 0, 0, 1},
										 {1, 1, 0, 0, 1, 0, 0, 1},
										 {0, 0, 0, 0, 0, 1, 1, 1},
										 {0, 0, 1, 0, 0, 1, 1, 1},
										 {0, 0, 1, 0, 0, 0, 1, 1},
										 {1, 0, 0, 0, 1, 0, 0, 0},
										 {1, 1, 0, 0, 1, 0, 0, 1},
										 {0, 1, 0, 1, 0, 0, 0, 0}};
	std::vector<std::vector<int>> arr_labeled;
	arr_labeled.resize(arr.size());
	for(std::vector<int> &a : arr_labeled)
	{
		a.resize(arr[0].size());
	}

	cluster(arr, arr_labeled);
	printArr2d(arr_labeled);
	/*create(&arr, row, col, default_val);

	std::string map_str="1000100010001111";

	stringTo2DArray(map_str, &arr, row, col);

	pathfinder(arr, row, col, 0, (row*col)-1);

	print(arr, row, col);*/


	vector<vector<int>> matrix = {{1,3,5,7},{10,11,16,20},{23,30,34,60}};
	int target = 3;
	bool result = find(matrix, target);
	printArr2d(matrix);
	cout << (result ? "FOUND " : "NOT FOUND ") << target << " in matrix." << endl;

	return 0;
}
