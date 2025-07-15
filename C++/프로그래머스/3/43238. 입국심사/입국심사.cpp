#include <string>
#include <vector>

using namespace std;

long long solution(int n, vector<int> times) {
    long long answer = 0;
    
    long long left = 0;
    long long right = (long long)times.back()*n;
    answer = right;
    long long mid = (left + right) / 2;
    
    while(left <= right){
        long long m = 0;
        mid = (left + right) / 2;
        
        for(auto t : times){
            m += mid / t;
        }
        if(m >= n){
            answer = mid;
            right = mid - 1;
        }
        else{
            left = mid + 1;
        }
    }
    
    return answer;
}

// 최대 시간이 걸릴 경우를 계산
// 그 경우에서 계산한 인원이 n 이하일 경우 right = mid
// n이상일 경우 left = mid