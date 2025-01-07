#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
Given an integer array nums, return all the triplets 
[nums[i], nums[j], nums[k]] such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.
Notice that the solution set must not contain duplicate triplets.
*/


vector<vector<int>> threeSum(vector<int>& nums) 
{
	vector<vector<int>> result;

	sort(nums.begin(), nums.end());
	
	for(int i = 0; i < nums.size() - 2; i++)
	{

		if(i > 0 && nums[i] == nums[i-1])
		{
			continue;
		}

		int target = -nums[i];
		int j = i+1;
		int k = nums.size() - 1;

		while(j < k)
		{
			int sum = nums[j] + nums[k];
			if(sum == target)
			{
				result.push_back(vector<int>{nums[i], nums[j], nums[k]});
				while(j < k && nums[j] == nums[j+1])
				{
					j++;
				}

				while(j < k && nums[k] == nums[k-1])
				{
					k--;
				}
			}

			if(sum < target)
			{
				j++;
			}
			else
			{
				k--;
			}
		}
	}
	return result;
}

int main(int argc, char **argv) 
{

	vector<int> arr = {-1,0,1,2,-1,-4};
	vector<vector<int>> result = threeSum(arr);

	for(vector<int> &vect : result)
	{
		for(int i : vect)
		{
			cout << i << " ";
		}
		cout << endl;
	}

	return 0;
}
