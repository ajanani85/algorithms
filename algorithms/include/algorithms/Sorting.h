/*
 * Sorting.h
 *
 *  Created on: Jan 2, 2019
 *      Author: ubuntu
 */

#ifndef ALGORITHMS_ALGORITHMS_INCLUDE_ALGORITHMS_SORTING_H_
#define ALGORITHMS_ALGORITHMS_INCLUDE_ALGORITHMS_SORTING_H_

namespace aj
{
class Sort
{
private:

public:
	Sort();
	~Sort();

	/*
	 *	Assertion sort algorithm.
	 *	Template.
	 *	Returns pointer
	 */
	template<class T>
	void insertion(T* arr, int n)
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
	void insertion(std::vector<T> arr)
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
};
}



#endif /* ALGORITHMS_ALGORITHMS_INCLUDE_ALGORITHMS_SORTING_H_ */
