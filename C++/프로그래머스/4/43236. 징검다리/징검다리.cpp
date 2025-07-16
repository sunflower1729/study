#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int solution(int distance, vector<int> rocks, int n) {
    vector<int> rock_dis;
    int answer = 0;
    
    sort(rocks.begin(), rocks.end());
    
    rock_dis.push_back(rocks[0]);
    for(int i = 1; i < rocks.size(); i++){
        rock_dis.push_back(rocks[i] - rocks[i-1]);
    }    
    rock_dis.push_back(distance - rocks.back());
    
    int left = 1;
    int right = distance;
    
    while(left <= right){
        
        int mid = (right + left) / 2;
        
        int temp = 0;
        int erase = 0;
        for(int i = 0; i < rock_dis.size(); i++){
            temp += rock_dis[i];
            if(temp < mid){
                erase++;
            }
            else{
                temp = 0;
            }
        }
        
        
        if(erase > n){
            right = mid - 1;
        }
        else{
            left = mid + 1;
            answer = mid;
        }
    }
    
    return answer;
}
