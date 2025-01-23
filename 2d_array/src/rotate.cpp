
#include <vector>
#include <iostream>

using namespace std;

void print(const std::string &prefix, const vector<vector<int>> &image)
{
    cout << prefix << " " << endl;
    int rows = image.size();
    int cols = image[0].size();
    for(int r = 0; r < rows; r++)
    {
        for(int c = 0; c < cols; c++)
        {
            cout << image[r][c] << " ";
        }
        cout << endl;
    }

    
}
vector<vector<int>> rotate90Clockwise(const vector<vector<int>>& matrix)
{
    int rows = matrix.size();
    int cols = matrix[0].size();

    vector<vector<int>> rotated(cols, vector<int>(rows));

    for(int r = 0; r < rows; r++)
    {
        for(int c = 0; c < cols; c++)
        {
            rotated[c][rows-r-1] = matrix[r][c]; 
        }
    }

    return rotated;
}

vector<vector<int>> rotate90CounterClockwise(const vector<vector<int>>& matrix)
{
    int rows = matrix.size();
    int cols = matrix[0].size();

    vector<vector<int>> rotated(cols, vector<int>(rows));

    for(int r = 0; r < rows; r++)
    {
        for(int c = 0; c < cols; c++)
        {
            rotated[cols - c - 1][r] = matrix[r][c];
        }
    }

    return rotated;
}

int main() {
    // Example input matrix (n x m)
    vector<vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
        {10, 11, 12}
    };

    cout << "Original Matrix:" << endl;
    print("original",matrix);

    // Rotate the matrix
    vector<vector<int>> rotated = rotate90Clockwise(matrix);
    print("clockwise rotated: ",rotated);


    rotated = rotate90CounterClockwise(matrix);
    print("counter clockwise rotated: ",rotated);

    return 0;
}