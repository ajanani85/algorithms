#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

void print(const vector<int> &vect, const std::string &prefix)
{
	cout << prefix << ":" << endl;
	for(const int i : vect)
	{
		cout << i << " ";
	}

	cout << endl;
}

/*
Given an array arr of 0s and 1s. Find and return the length of the longest subarray with equal number of 0s and 1s. in C++
The same solution can be applied to finding the subarray of any two numbers 1s and 2s
*/
void longestSubArrayWith0sAnd1s() 
{
	vector<int> arr = {0, 1, 0, 1, 1, 1, 0, 0};
	print(arr, __func__);

	int prefixSum = 0;
	int maxLen = 0;
	unordered_map<int,int> map;
	
	//assume 0 is -1 and 1 is 1
	int n = arr.size();
	for(int i = 0; i < n; i++)
	{
		prefixSum += arr[i] == 0 ? -1 : 1;

		if(prefixSum == 0)
		{
			maxLen = i+1;
		}

		if(map.find(prefixSum) != map.end())
		{
			maxLen = max(maxLen, i - map[prefixSum]);
		}
		else 
		{
			map[prefixSum] = i;
		}
	}

	cout << maxLen << endl;

}

/*
Given an array, find the length of the longest subarray that sums up to K
*/


void longestSubArrayWithSumK()
{
	vector<int> arr = {10, 5, 2, 7, 1, -10};
	int k = 15;

	print(arr, __func__);

	unordered_map<int,int> map;
	int prefixSum = 0;
	int longestSum = 0;

	for(int i = 0; i < arr.size(); i++)
	{
		prefixSum += arr[i];

		if(prefixSum == k)
		{
			longestSum = i + 1;
		}

		if(map.find(prefixSum) != map.end())
		{
			longestSum = max(longestSum, i-map[prefixSum]);
		}

		else
		{
			map[prefixSum] = i;
		}
	}

	cout << longestSum << endl;
	
}

/*
Check if there exists a subarray with a sum of zero.
*/

void findSubArraySumWithZeroSum()
{
	vector<int> arr = {4, 2, -3, 1, 6};

	int prefixSum = 0;
	print(arr, __func__);

	unordered_map<int,int> map;
	bool result = false;

	for(int i = 0; i < arr.size(); i++)
	{
		prefixSum += arr[i];

		if(prefixSum == 0 || map.find(prefixSum) != map.end())
		{
			result = true;
		}

		map[prefixSum] = i;
	}

	cout << result << endl;
}



/*
Count the number of subarrays in an array that sum up to k
*/
void countOfSubarraysWithSum()
{
	vector<int> arr = {10, 2, -2, -20, 10};
	print(arr, __func__);
	int k = -10;
	int counter = 0;
	int prefixSum = 0;
	unordered_map<int,int> map;

	for(int i = 0; i < arr.size(); i++)
	{
		prefixSum += arr[i];

		if(prefixSum == k)
		{
			counter++;
		}

		if(map.find(prefixSum-k) != map.end())
		{
			counter += map[prefixSum-k];
		}

		map[prefixSum]++;


	}

	cout << counter << endl;

}

/*
	Given an array, find if there exists a pair of elements whose sum equals K
*/

void findPairWithTargetSum()
{
	vector<int> arr = {1, 4, 45, 6, 10, 8};
	int k = 16;
	print(arr, __func__);
	unordered_set<int> set;
	bool result = false;

	for(int i = 0; i < arr.size(); i++)
	{
		if(set.find(arr[i]) != set.end())
		{
			result = true;
			break;
		}
		
		set.insert(k-arr[i]);
	}
	
	cout << result << endl;
}



int main(int argc, char **argv) 
{

	vector<int> arr = {-1,0,1,2,-1,-4};
	
	longestSubArrayWith0sAnd1s();
	longestSubArrayWithSumK();
	countOfSubarraysWithSum();
	findPairWithTargetSum();
	findSubArraySumWithZeroSum();
	return 0;
}
