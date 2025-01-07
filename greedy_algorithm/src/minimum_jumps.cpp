#include <iostream>
#include <vector>
using namespace std;


int minJumpsGreedy(vector<int> &arr) 
{
	int farthest_index = 0;
	int jump = 0;
	int current_end_index = 0;

	for(int i  = 0 ; i < arr.size(); i++)
	{
		farthest_index = max(farthest_index , arr[i] + i);
		if(current_end_index == i)
		{
			jump++;
			current_end_index = farthest_index;
		}
		if(current_end_index == arr.size() - 1)
		{
			return jump;
		}
	}

	return -1;
}



bool canJump(vector<int> arr)
{
	int n = arr.size();
	int farthestJump = 0;

	for(int i = 0; i < n; i++)
	{
		
		if(i > farthestJump)
		{
			return false;
		}

		farthestJump = max(farthestJump, i + arr[i]);

		if(farthestJump >= n-1)
		{
			return true;
		}
	}

	return false;
}

int main() {
    vector<int> arr = {2, 3, 1, 1, 2, 4, 2, 0, 1, 1};

	cout << (canJump(arr) ? "The array can be jumpped" : "The array cannot be jumpped") << endl;

    cout << minJumpsGreedy(arr) << endl;
    return 0;
}
