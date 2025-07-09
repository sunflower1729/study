#include <string>
#include <vector>
#include <iostream>

using namespace std;

int solution(vector<vector<int>> sizes) {
    int max_l = max(sizes[0][0],sizes[0][1]);
    int min_l = min(sizes[0][0],sizes[0][1]);
    
    for(int i = 1; i<sizes.size(); i++){
        max_l = max(max(sizes[i][0],sizes[i][1]), max_l);
        min_l = max(min(sizes[i][0],sizes[i][1]), min_l);
    }
    
    return max_l*min_l;
}