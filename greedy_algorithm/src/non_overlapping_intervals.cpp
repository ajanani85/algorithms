#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
The Activity Selection Problem is a classic example of a greedy algorithm. 
The goal is to select the maximum number of activities that don't overlap in 
terms of start and finish times. 

Problem Statement:
Given n activities with their start and end times, select the maximum number of 
activities that can be performed by a single person, assuming that a person can only work on one activity at a time.
*/

struct Activity
{
	/* data */
	int start;
	int end;
};

bool comapreActivities(const Activity &a, const Activity &b)
{
	return a.end < b.end;
}

std::vector<Activity> getNonOverlappingActivities(std::vector<Activity> activities)
{

	std::vector<Activity> result;

	//1. sort the activities according to their end time
	sort(activities.begin(), activities.end(), comapreActivities);

	//2. Add the first item in the list to the result
	result.push_back(activities[0]);

	//3. Iterate through the list of activities and compare the end of one activity with the start of the next
	int lastEndTime = activities[0].end;

	for(int i = 1; i<activities.size(); i++)
	{
		if(activities[i].start >= lastEndTime)
		{
			result.push_back(activities[i]);
			lastEndTime = activities[i].end;
		}
	}

	return result;
}

int main(int argc, char **argv) 
{

	// Define a set of activities with their start and end times
    std::vector<Activity> activities = {
        {1, 3}, {0, 3}, {4, 6}, {6, 7}, {5, 8}, {8, 9}
    };

	std::vector<Activity> selectedActivities;

	selectedActivities = getNonOverlappingActivities(activities);

	// Print selected activities
    std::cout << "Selected Activities: \n";
    for (const auto &activity : selectedActivities) {
        std::cout << "Start: " << activity.start << ", End: " << activity.end << "\n";
    }
	return 0;
}
