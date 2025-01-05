#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
determine the maximum number of intervals that overlap at any point in time.

The Sweep Line Algorithm
*/

struct Event
{
	int time;
	int type;
};

struct Activity
{
	/* data */
	int start;
	int end;
};

bool compareEvents(const Event &a, const Event &b)
{
	if(a.time == b.time)
	{
		return a.type < b.type;
	}
	return a.time < b.time;
}

int maximumOverlappingIntervals(const std::vector<Activity> &activities) 
{
	//1. convert the intervals into Events time and type-> 1 for start and -1 for end
	vector<Event> events;
	for(const Activity &ac : activities)
	{
		events.push_back({ac.start, 1});
		events.push_back({ac.end, -1});
	}

	//2. Sort the events according to their time and type
	sort(events.begin(), events.end(), compareEvents);

	//3. Process the events
	int maxInterval = 0;
	int sumIntervals = 0;
	for(Event &e : events)
	{
		sumIntervals += e.type;
		maxInterval=max(maxInterval, sumIntervals);
	}

	return maxInterval;
}

int main(int argc, char **argv) 
{

	// Example intervals
    std::vector<Activity> intervals = {{1, 3}, {2, 5}, {4, 6}};

    int result = maximumOverlappingIntervals(intervals);
    std::cout << "Maximum number of overlapping intervals: " << result << std::endl;

    return 0;
}
