#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <math.h>
#include <unordered_map>
#include <unordered_set>

using namespace std;

std::vector<std::string> readFile(const std::string &path)
{
    std::vector<std::string> fileContents;
    std::ifstream file(path); // Open the file

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file at " << path << std::endl;
        return fileContents; // Return empty vector if file can't be opened
    }

    std::string line;
    while (std::getline(file, line)) {
        fileContents.push_back(line); // Add each line to the vector
    }

    file.close(); // Close the file
    return fileContents;
}

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

void to2DArray(const std::vector<int> &raw_image, std::vector<std::vector<int>> &two_d_array)
{
    int size = raw_image.size();
    int dimension = std::sqrt(size);

    // Check if the array size is a perfect square
    if (dimension * dimension != size) {
        std::cerr << "Error: The size of the array (" << size 
                  << ") is not a perfect square." << std::endl;
        return;
    }

    two_d_array = std::vector<std::vector<int>>(dimension, std::vector<int>(dimension));
    for (int i = 0; i < size; ++i) {
        two_d_array[i / dimension][i % dimension] = raw_image[i];
    }

    return; 

}

void toTestCase(std::vector<std::string> &raw_tests, std::vector<std::vector<std::vector<int>>> &images, bool print_flag)
{
    int cnt = 0;
    for( std::string &raw_test : raw_tests)
    {
        std::vector<int> raw_image;
        stringstream ss(raw_test);
        string token;
        while(getline(ss, token, ','))
        {
            try 
            {
                raw_image.push_back(std::stoi(token)); // Convert token to integer and add to vector
            } catch (const std::invalid_argument& e) {
                std::cerr << "Invalid integer in file: " << token << std::endl;
            }
        }
        std::vector<std::vector<int>> image;
        to2DArray(raw_image, image);
        if(print_flag)
        {
            string msg = string("test_") + to_string(cnt);
            print(msg, image);
        }
        images.push_back(image);
    }


}

void dfs(std::vector<std::vector<int>> &image, unordered_set<int> &visited, unordered_map<int, int> &clusters, int row, int col, int &cluster_cnt)
{
    int idx = row * image.size() + col;
    //if it is visited already or the value is zero return, simply just return
    if(visited.find(idx) != visited.end() || image[row][col] == 0)
    {
        return;
    }

    visited.insert(idx);

    //setup the search window
    int dimension = image.size();

    int c_l = max(0, col - 1);
    int c_h = min(dimension-1, col + 1);
    int r_l = max(0, row- 1);
    int r_h = min(dimension-1, row+1);

    //cout << "for r: " << row << " c: " << col << " value: " << image[row][col] << " c_l: " << c_l << ", c_h: " << c_h << ", r_l: " << r_l << ", r_h: " << r_h << endl; 

    for(int r = r_l; r <= r_h; r++)
    {
        for(int c = c_l; c <= c_h; c++)
        {
            int idx_t = r * dimension + c;
            if( idx_t == idx)
            {
                continue;
            }
            dfs(image, visited, clusters, r, c, cluster_cnt);

            
            if(clusters.find(idx_t) != clusters.end())
            {
                clusters[idx] = clusters.find(idx_t)->second;
            }
            
        }
    }
    if(clusters.find(idx) == clusters.end())
    {
        cluster_cnt++;
        clusters.insert(make_pair(idx, cluster_cnt));
    }
}

void findFeatures(std::vector<std::vector<int>> &image, std::vector<std::vector<int>> &res)
{
    //key: 1D index, value: cluster id >= 1
    unordered_map<int, int> clusters;

    //visited list
    unordered_set<int> visited;
    
    //run the depth search first
    int cluster_cnt = 1;
    int n = image.size();
    for(int r = 0; r < n; r++)
    {
        for(int c = 0; c < n; c++)
        {
            dfs(image, visited, clusters, r, c, cluster_cnt);
        }
    }
    

    //convert clusters to vectors
    unordered_map<int, int>::iterator it = clusters.begin();
    for(; it != clusters.end(); ++it)
    {
        int dimension = image.size();
        int r = it->first/dimension;
        int c = it->first%dimension;

        image[r][c] = it->second;
    }

    res = image;
}
    

int main(int argc, char** argv)
{

    std::string testFilePath = "../test/dfs.txt";

    std::vector<std::string> raw_tests = readFile(testFilePath);

    //cout << raw_tests[0] << endl;

    std::vector<std::vector<std::vector<int>>> images;

    toTestCase(raw_tests, images, true);

    for(std::vector<std::vector<int>> &image : images)
    {
        std::vector<std::vector<int>> labelled_image;
        findFeatures(image, labelled_image);
        print("labelled: ", labelled_image);
    }

    return 0;
}