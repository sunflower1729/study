#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void swap(vector<int> &a){
    int temp = a[0];
    a[0] = a[1];
    a[1] = temp;
}

int solution(vector<vector<int>> sizes) {
    int answer = 0;
    int max = 0;
    
    for(auto &a : sizes){
        if(max < a[0]) {
            max = a[0];
            swap(a);
        }
        if(max < a[1])
            max = a[1];
    }
    sort(sizes.rbegin(), sizes.rend());
    
    for(auto a : sizes){
        cout << a[0] << " " << a[1] << endl;
    }
    
    int max2 = 0;
    //answer = sizes[0][0] * sizes[0][1];
    for(auto a : sizes){
        cout << "\n" << a[0] << " " << a[1] << endl;
        if( a[0] > a[1]){
            swap(a);
            if(max2 < a[0])
                max2 = a[0];
        }
        else{
            if(max2 < a[0])
                max2 = a[0];
            answer = max2 * max;
            break;
        }
    }
    return answer;
}                                        