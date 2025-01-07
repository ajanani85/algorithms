#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int minJumpsDP(vector<int> arr) 
{
	vector<int> dp(arr.size(), INT_MAX);
	dp[0] = 0;

	for(int i = 0; i < arr.size() - 1; i++)
	{
		for(int j = i +1; j <= i + arr[i] && j < arr.size(); j++)
		{
			dp[j] = min(dp[j], dp[i]+1);
		}
	}

	return (dp[dp.size() - 1] == INT_MAX ? -1 : dp[dp.size() - 1]);

}

int main() {
    vector<int> arr = {2, 3, 1, 1, 2, 4, 2, 0, 1, 1};
    int result = minJumpsDP(arr);
    cout << (result == INT_MAX ? -1 : result) << endl;
    return 0;
}