#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;


int solution(vector<int> scoville, int K) {
    priority_queue<int, vector<int>, greater<int>> pq;
    int answer = 0;
    
    for(int sco : scoville){
        pq.push(sco);
    }
    while(pq.top() < K){
        if(pq.size() == 1){
            answer = -1;
            break;
        }
        int a = pq.top();
        pq.pop();
        int b = pq.top();
        pq.pop();
        pq.push(a + b*2);
        answer++;
    }
    
    return answer;
}