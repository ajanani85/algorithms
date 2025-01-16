
#include <vector>
#include <iostream>
#include <string>
#include <memory>
#include <algorithm>
#include <climits>
#include <queue>

using namespace std;

vector<vector<int>> neighbors = {{1,0},{0,1},{-1,0},{-1,-1}};

pair<int, vector<pair<int, int>>> djikstra(vector<vector<int>> &grid, const pair<int,int> &start, const pair<int,int> &end)
{
    int n = grid.size();
    int m = grid[0].size();
    
    // Distance matrix to store the shortest distance to each cell
    vector<vector<int>> dist(n, vector<int>(m,INT_MAX));
    dist[start.first][start.second] = 0;

    // Parent matrix to store the parent of each cell in the shortest path
    vector<vector<pair<int, int>>> parent(n, vector<pair<int, int>>(m, {-1, -1}));

    // Min-heap to store (distance, (x, y))
    priority_queue<pair<int, pair<int,int>>, vector<pair<int, pair<int,int>>>, greater<pair<int, pair<int,int>>>> pq;
    pq.push({0, start});

    while(!pq.empty())
    {
        pair<int,int> currCell = pq.top().second;
        int currDist = pq.top().first;
        pq.pop();

        //check if we are at the end
        if(currCell.first == end.first && currCell.second == end.second)
        {
            vector<pair<int, int>> path;
            pair<int, int> curr = {currCell.first, currCell.second};

            // Backtrack from destination to source using the parent matrix
            while (curr != make_pair(-1, -1)) {
                path.push_back(curr);
                curr = parent[curr.first][curr.second];
            }

            reverse(path.begin(), path.end());
            return {currDist, path};

        }

        //process the neighbours
        for(vector<int> &side : neighbors)
        {
            int r = min(max(0, side[0] + currCell.first), n-1);
            int c = min(max(0, side[0] + currCell.second), m-1);

            if(grid[r][c] != 0)
            {
                continue;
            }
            if(currDist + 1 < dist[r][c])
            {
                dist[r][c] == currDist + 1;
                parent[r][c] = {currCell.first, currCell.second};    // Update the parent
                pq.push({dist[r][c], {currCell.first, currCell.second}}); // Push neighbor to priority queue
            }

        }

        return {-1, {}};

    }


}

void print(vector<vector<int>> &grid)
{
    for(int r = 0; r < grid.size(); r++)
    {
        for(int c = 0; c < grid[0].size(); c++)
        {
            cout << grid[r][c] << " ";
        }
        cout << endl;
    }
}

void print(pair<int, vector<pair<int, int>>> &paths)
{
    if (paths.first == -1) {
        cout << "The shortest path distance is: " << paths.first << endl;
        cout << "The path is:" << endl;
        for (const auto& [row, col] : paths.second) {
            cout << "(" << row << ", " << col << ") ";
        }
        cout << endl;
    } 
}

int main(int argc, char** argv)
{
    vector<vector<int>> grid = {
        {0, 0, 1, 0, 0},
        {1, 0, 1, 0, 1},
        {0, 0, 0, 0, 0},
        {1, 1, 1, 1, 0},
        {0, 0, 0, 1, 0}
    };

    pair<int,int> start = {0,0};
    pair<int,int> end = {grid.size() - 1, grid.size() - 1};

    print(grid);

    pair<int, vector<pair<int, int>>> paths = djikstra(grid, start, end);

    print(paths);

    return 0;
}