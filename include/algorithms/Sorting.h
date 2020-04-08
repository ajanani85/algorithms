/*
 * Sorting.h
 *
 *  Created on: Jan 2, 2019
 *      Author: ubuntu
 */

#ifndef ALGORITHMS_ALGORITHMS_INCLUDE_ALGORITHMS_SORTING_H_
#define ALGORITHMS_ALGORITHMS_INCLUDE_ALGORITHMS_SORTING_H_

#include <iostream>
#include <vector>

namespace aj
{
class Sort
{
private:

public:
	Sort();
	~Sort();

	//utility functions
	template<class T>
	static void print(T* arr, int n)
	{
		for(int i = 0; i < n; ++i)
		{
			std::cout << " " << arr[i];
		}
		std::cout << std::endl;
	}


	template<class T>
	static void print(std::vector<T> &arr)
	{
		for(int i = 0; i < arr.size(); i++)
		{
			std::cout << " " << arr[i];
		}
		std::cout << std::endl;
	}

	template<class T>
	static void swap(T &a, T &b)
	{
		T c(a);
		a = b;
		b = c;
	}
	/*
	 *	Insertion sort algorithm.
	 *	Template
	 *	time complexity = O(n^2)
	 *	space complexity = O(1)
	 */
	template<class T>
	static void insertion(T* arr, int n)
	{
		//Iterate through each component in the passed array
		//Forget about the first component (0)
		for(int i = 1; i < n; ++i)
		{
			//make a copy of the current component
			T tmp = arr[i];
			int j = i-1;
			while(j >= 0 && arr[j] > tmp)
			{
				arr[j+1] = arr[j];
				j = j - 1;
			}
			arr[j+1] = tmp;
		}
	}

	template<class T>
	static void insertion(std::vector<T> &arr)
	{
		for(int i = 1; i < arr.size(); ++i)
		{
			T tmp = arr[i];
			int j = i - 1;
			while(j >= 0 && arr[j] > tmp)
			{
				arr[j+1] = arr[j];
				j = j - 1;
			}
			arr[j+1] = tmp;
		}
	}

	/*
	 *  Selection Sort Algorithm
	 *	Template
	 *	time complexity = O(n^2)
	 *	space complexity = O(1)
	 */
	template<class T>
	static void selection(T* arr, int n)
	{
		//iterate through the array
		for(int i = 0; i < n - 1; i++)
		{
			//find minimum in the unsorted array
			int min_idx = i;
			for(int j = i; j < n; j++)
			{
				if(arr[j] < arr[min_idx])
				{
					min_idx = j;
				}
			}

			Sort::swap(&arr[min_idx], &arr[i]);
		}
	}

	template<class T>
	static void selection(std::vector<T> &arr)
	{
		for(int i = 0; i < arr.size(); ++i)
		{

			//find minimum
			int min_idx = i;
			for(int j = i; j < arr.size(); ++j)
			{
				if(arr[j] < arr[min_idx])
				{
					min_idx = j;
				}
			}
			Sort::swap(&arr[i], &arr[min_idx]);
		}
	}


	template<class T>
	static void bubble(T* arr, int n)
	{

	}

	/*
	 * Bubble Sort Optimized:
	 * time Complexity: O(n^2)
	 * space complexity: O(1)
	 */
	template<class T>
	static void bubbleOptimized(T* arr, int n)
	{
		bool notSroted = true;
		while(notSroted)
		{
			notSroted = false;
			for(int i = 0; i < n-1; i++)
			{
				if(arr[i] < arr[i+1])
				{
					Sort::swap(&arr[i], &arr[i+1]);
					notSroted = true;
				}
			}
		}
	}
	template<class T>
	static void bubleOptimized(std::vector<T> &arr)
	{
		bool notSorted = true;
		while(notSorted)
		{
			notSorted = false;
			for(int i = 0; i < arr.size() - 1; i++)
			{
				if(arr[i] > arr[i+1])
				{
					Sort::swap(&arr[i], &arr[i+1]);
					notSorted = true;
				}
			}
		}
	}

};
}



#endif /* ALGORITHMS_ALGORITHMS_INCLUDE_ALGORITHMS_SORTING_H_ */
