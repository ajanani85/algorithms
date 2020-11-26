#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include <set>
#include <math.h>
using namespace std;

void print(const vector<int> &arr)
{
	for(int i = 0; i < arr.size(); i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

/*
 * Reverse a string without affecting special characters
 * Given a string, that contains special character together with alphabets (‘a’ to ‘z’ and ‘A’ to ‘Z’),
 * reverse the string in a way that special characters are not affected.
 * Example:
 * input: a,b$c
 * output: c,b$a;
 */
bool isAlphabet(char c)
{
	//int i = c;
	//if((i >= 65 && i <= 90) || (i >= 97 && i <= 122))
	if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
	{
		return true;
	}

	return false;
}

void reverseOrder(std::string &str)
{
	cout << str << endl;
	int low = 0;
	int high = str.length() - 1;

	while(low < high)
	{
		if(!isAlphabet(str[low]))
		{
			low++;
			continue;
		}

		if(!isAlphabet(str[high]))
		{
			high--;
			continue;
		}

		std::swap(str[low], str[high]);
		low++;
		high--;
	}

	cout << str << endl;
}

/*
 * How do you find the missing number in a given integer array of 1 to 100?
 */
int findTheMissingNumber(const std::vector<int> &arr)
{
	int sum = arr.size() * (arr.size()-1)/2;

	for(int i = 0; i < arr.size(); i++)
	{
		sum -= arr[i];
	}
	return sum;
}

/*
 * How do you find the duplicate number on a given integer array?
 * Example: array = {1,2,3,4,4,5,6}
 * output: 4
 */
int findDuplicate(std::vector<int> &arr)
{
	//ordering the arr
	std::sort(arr.begin(), arr.end());
	for(int i = 0; i < arr.size() - 1; i++)
	{
		if(arr[i] == arr[i+1])
		{
			return arr[i];
		}
	}
	return -1;

	//using another container
	std::unordered_set<int> set;
	for(int i = 0; i < arr.size(); i++)
	{
		if(set.find(arr[i]) != set.end())
		{
			return arr[i];
		}
		set.insert(arr[i]);
	}
	return -1;
}

/**
 * How do you find duplicate numbers in an array if it contains multiple duplicates?
 */
void findDuplicates(std::vector<int> &arr)
{
	//approach 1
	std::sort(arr.begin(), arr.end());

	for(int i = 0; i < arr.size() - 1; i++)
	{
		if(arr[i] == arr[i+1])
		{
			printf("found duplicate %d, [%d,%d]\n", arr[i], i, i+1);
		}
	}

	//approach 2
	printf("approach 2\n");
	unordered_map<int,int> map;
	for(int i = 0; i < arr.size(); i++)
	{
		if(map.find(arr[i]) != map.end())
		{
			printf("found duplicate %d, [%d,%d]\n", arr[i], i, map[arr[i]]);
			continue;
		}
		map[arr[i]] = i;
	}
}

/**
 * How are duplicates removed from a given array
 * Example:
 * input: {1,2,3,1,4,5}
 * output: {1,2,3,4,5}
 */
void removeDuplicates(std::vector<int> &arr)
{
	//approach 2
	unordered_set<int> set;

	int idx = -1;
	for(int i = 0; i < arr.size(); i++)
	{
		if(set.find(arr[i]) != set.end())
		{
			continue;
		}
		idx++;
		if(idx != i)
		{
			std::swap(arr[i], arr[idx]);
		}
		set.insert(arr[i]);
	}

	if(idx > 0)
	{
		arr.resize(idx);
		return;
	}
	 if(idx == 0)
	 {
		 arr.resize(1);
	 }
	 return;
}

/**
 * How do you find the largest and smallest number in an unsorted integer array?
 * Example:
 * input: {0,-1,6,-10,20,8,-9};
 * output: -10 and 20
 */
void printLargestSmallest(const std::vector<int> &arr)
{
	if(arr.size() == 0)
	{
		return;
	}
	int smallest = arr[0];
	int largest = arr[0];
	for(int i = 1; i < arr.size(); i++)
	{
		if(arr[i] > largest)
		{
			largest = arr[i];
			continue;
		}
		if(arr[i] < smallest)
		{
			smallest = arr[i];
		}
	}

	cout << "largest: " << largest << " and " << "smallest: " << smallest << endl;
}

/**
 * How do you find all pairs of an integer array whose sum is equal to a given number?
 * Example:
 * input: {1, 0, 2, 1, -2, 4}, sum: 2
 * output: [1,1] [0,2] [-2,4]
 */
void findPairWithSum(const std::vector<int> &arr, int sum)
{
	//approach 1
	for(int i = 0; i < arr.size() - 1; i++)
	{
		for(int j = i + 1; j < arr.size(); j++)
		{
			if(arr[i] + arr[j] == sum)
			{
				printf("pair[%d, %d] at i: %d and %d\n", arr[i], arr[j], i, j);
			}
		}
	}

	//approach 2
	printf("approach 2\n");
	std::unordered_multimap<int, int> map;
	for(int i = 0; i < arr.size(); i++)
	{

		std::unordered_multimap<int, int>::iterator it = map.find(sum - arr[i]);
		while(it != map.end() && it->first == sum-arr[i])
		{
			printf("pair[%d, %d] at i: %d and %d\n", arr[it->second], arr[i], it->second,i);
			++it;
		}
		map.insert(std::make_pair(arr[i],i));
	}
}


/*
 * reverse an array in place
 * Example:
 * input: {1,2,3,4,5}
 * output: {5,4,3,2,1}
 */
void reverse(std::vector<int> &arr)
{
	for(int i = 0; i < arr.size() / 2; i++)
	{
		std::swap(arr[i], arr[arr.size() - i - 1]);
	}
}

void findAllPrimeFactors(int n)
{
	std::list<uint64_t> result;
	std::set<uint64_t> list;
	 while (n%2 == 0){
	      cout<<"2\t";
	      list.insert(2);
	      n = n/2;
	   }
	   for (uint64_t i = 3; i <= sqrt(n); i = i+2){
	      while (n%i == 0){
	         cout<<i<<"\t";
	         list.insert(i);
	         n = n/i;
	      }
	   }
	   if (n > 2)
	   cout<<n<<"\t";
	   list.insert(n);

	   for(std::set<uint64_t>::reverse_iterator rit = list.rbegin(); rit != list.rend(); ++rit)
	   {
		   result.push_back(*rit);
	   }

}

bool is_prime(uint64_t n)
{
	if (n <= 1)
	{
		return false;

	}
  // Check from 2 to n-1
  for (uint64_t i = 2; i < n; i++)
  {
	  if (n % i == 0)
	  {
		  return false;
	  }
  }
  return true;
}

int main(int argc, char **argv) {

	std::vector<char> data_;
	std::ifstream infile("test.txt");

	//get length of file
	infile.seekg(0, std::ios::end);
	size_t length = infile.tellg();
	infile.seekg(0, std::ios::beg);

	data_.resize(length);
	char c;
	int cnt = 0;
	while (infile.get(c))
	{
		data_[cnt] = c;
		cnt++;
	}

	for(int i = data_.size() - 1; i >= data_.size() - 5; i--)
	{
		cout << data_[i] << " " << endl;
	}

	int sn_ = 3;
	int pk_ = 5;
	int sk_ = 15;

	std::ofstream out_file("letter.data");
	for(int val : data_)
	{
		uint64_t result = val;
		for(int j = 0; j < sk_ - 1; j++)
		{
			result *= val;
		}

		result %= sn_;
		out_file << result;
	}
	out_file.close();

	out_file.open("key.pub");
	out_file << "pk_" << "\n" << pk_;
	out_file.close();

	out_file.open("key.prv");
	out_file << "sk_" << "\n" << sk_;
	out_file.close();

	return 0;
}
