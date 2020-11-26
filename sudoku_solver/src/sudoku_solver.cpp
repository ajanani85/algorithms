#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <fstream>
#include <opencv2/opencv.hpp>

using namespace std;

int loadSudokuFromStr(int ***sudoku, const std::string &src);
void printSudoku(int **sudoku);
bool solve(int ***sudoku, int row, int col);
int whichSquare(int id);
int updateTable(int ***sudoku, std::unordered_map<int, std::unordered_set<int>> &rows_missing,
		std::unordered_map<int, std::unordered_set<int>> &cols_missing,
		std::unordered_map<int, std::unordered_set<int>> &squares_missing);
void print(const unordered_map<int, unordered_set<int>> &src, const std::string &msg);
void print(const unordered_set<int> &src, const std::string &msg);
unordered_set<int> findCommon(const unordered_set<int> &a, const unordered_set<int> &b);

unordered_set<int> findCommon(const unordered_set<int> &a, const unordered_set<int> &b)
{
	if(a.size() == 0 && b.size() == 0)
	{
		return unordered_set<int>();
	}
	if(a.size() == 0)
	{
		return b;
	}
	if(b.size() == 0)
	{
		return a;
	}


	unordered_set<int> tmp2 = a.size() > b.size() ? a : b;
	unordered_set<int> tmp = a.size() < b.size() ? a : b;
	unordered_set<int> result;

	for(unordered_set<int>::iterator it = tmp2.begin(); it!= tmp2.end(); ++it)
	{

		if(tmp.find(*it) == tmp.end())
		{
			continue;
		}
		result.insert(*it);
	}

	return result;

}

void print(const unordered_set<int> &src, const std::string &msg)
{
	cout << msg << endl;
	unordered_set<int>::const_iterator it_set = src.cbegin();
	for(; it_set != src.cend(); ++it_set)
	{
		cout << *it_set << " ";
	}
	cout << endl;
}

void print(const unordered_map<int, unordered_set<int>> &src, const std::string &msg)
{
	cout << msg << endl;
	unordered_map<int, unordered_set<int>>::const_iterator it = src.cbegin();
	for(; it != src.cend(); ++it)
	{
		cout << it->first << ": ";
		unordered_set<int>::const_iterator it_set = it->second.cbegin();
		for(; it_set != it->second.cend(); ++it_set)
		{
			cout << *it_set << " ";
		}
		cout << endl;
	}
}


int updateTable(int ***sudoku, std::unordered_map<int, std::unordered_set<int>> &rows_missing,
		std::unordered_map<int, std::unordered_set<int>> &cols_missing,
		std::unordered_map<int, std::unordered_set<int>> &squares_missing)
{
	unordered_set<int> tmp = {1,2,3,4,5,6,7,8,9};
	int numberOfZeros = 0;
	for(int i = 0; i < 9; i++)
	{
		rows_missing.insert(std::make_pair(i, tmp));
		cols_missing.insert(std::make_pair(i, tmp));
		squares_missing.insert(std::make_pair(i, tmp));
	}


	for(int r = 0; r < 9; r++)
	{
		for(int c = 0; c < 9; c++)
		{
			int idx = r * 9  + c;

			if((*sudoku)[r][c] != 0)
			{
				rows_missing[r].erase((*sudoku)[r][c]);
				cols_missing[c].erase((*sudoku)[r][c]);
				squares_missing[whichSquare(idx)].erase((*sudoku)[r][c]);
				continue;
			}
			numberOfZeros++;
		}
	}

	return numberOfZeros;
}

int whichSquare(int id)
{
	int row = id / 9;
	int col = id % 9;

	if(row >= 0 && row <= 2 && col >= 0 && col <= 2)
	{
		return 0;
	}
	if(row >= 0 && row <= 2 && col >= 3 && col <= 5)
	{
		return 1;
	}
	if(row >= 0 && row <= 2 && col >= 6 && col <= 8)
	{
		return 2;
	}

	if(row >= 3 && row <= 5 && col >= 0 && col <= 2)
	{
		return 3;
	}
	if(row >= 3 && row <= 5 && col >= 3 && col <= 5)
	{
		return 4;
	}
	if(row >= 3 && row <= 5 && col >= 6 && col <= 8)
	{
		return 5;
	}

	if(row >= 6 && row <= 8 && col >= 0 && col <= 2)
	{
		return 6;
	}
	if(row >= 6 && row <= 8 && col >= 3 && col <= 5)
	{
		return 7;
	}
	if(row >= 6 && row <= 8 && col >= 6 && col <= 8)
	{
		return 8;
	}

	return -1;
}

bool isPossible(int **sudoku, int r, int c, int n)
{
	//check rows
	for(int i = 0; i < 9; i++)
	{
		if(sudoku[r][i] == n)
		{
			return false;
		}
	}

	//check cols
	for(int i = 0; i < 9; i++)
	{
		if(sudoku[i][c] == n)
		{
			return false;
		}
	}


	//check squares
	int r_s = r / 3;
	int c_s = c / 3;
	int r_hbound = ((r_s + 1)*3)-1;
	int r_lbound = r_s * 3;
	int c_hbound = ((c_s + 1)*3)-1;
	int c_lbound = c_s * 3;
	//printf("at [%d %d] square idx [%d, %d], r_bound = [%d,%d] c_bound = [%d, %d]\n", r, c, r_s, c_s, r_lbound, r_hbound, c_lbound, c_hbound);
	for(int i = r_lbound; i <= r_hbound; i++)
	{
		for(int j = c_s * 3; j <= ((c_s + 1)*3)-1; j++)
		{
			if(sudoku[i][j] == n)
			{
				return false;
			}
		}
	}

	return true;
}

bool solve(int ***sudoku, int row, int col)
{
	//printf("checking for %d and %d\n", row, col);
	if(sudoku == NULL)
	{
		return false;
	}

	if(row == 8 && col == 9)
	{
		return true;
	}

	if(col == 9)
	{
		row++;
		col = 0;
	}

	if((*sudoku)[row][col] != 0)
	{
		return solve(sudoku, row, col+1);
	}

	for(int i = 1; i < 10; i++)
	{
		if(isPossible(*sudoku, row, col, i))
		{
			(*sudoku)[row][col] = i;
			if(solve(sudoku, row, col+1))
			{
				return true;
			}
		}
		(*sudoku)[row][col] = 0;
	}

	return false;
}

int loadSudokuFromStr(int ***sudoku, const std::string &src)
{
	if(src.size() != 81)
	{
		return -1;
	}

	//create a 2d array
	*sudoku = new int*[9];
	for(int i = 0; i<9; i++)
	{
		(*sudoku)[i] = new int[9];
	}

	//load the table
	for(int i = 0; i < src.size(); i++)
	{
		int number = src[i]-'0';
		if(number < 0 || number > 9)
		{
			return -1;
		}

		int r = i / 9;
		int c = i % 9;
		(*sudoku)[r][c] = number;
	}

	int i = 0;
	return 0;

}


void printSudoku(int **sudoku)
{
	if(sudoku == NULL)
	{
		return;
	}
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			cout << sudoku[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

int main(int argc, char **argv) {

	cv::Mat img_raw;
	img_raw = cv::imread("/home/ubuntu/eclipse_ws/algorithms/sudoku_solver/images/sudoku1.png");

	cv::resize(img_raw,img_raw,cv::Size(500,500));

	cv::imshow("test", img_raw);

	if(cv::waitKey() == 30)
	{

	}

	/*

	std::vector<std::string> sudokus;
	std::ifstream file("/home/ubuntu/eclipse_ws/algorithms/sudoku_solver/test/sudoku.txt");
	if(file.is_open())
	{
		std::string line;
		while(getline(file, line))
		{
			sudokus.push_back(line);
		}
	}

	for(const std::string sudoku_str : sudokus)
	{
		int **sudoku = NULL;

		loadSudokuFromStr(&sudoku, sudoku_str);

		printSudoku(sudoku);

		solve(&sudoku, 0, 0);

		printSudoku(sudoku);
	}*/


	return 0;
}
