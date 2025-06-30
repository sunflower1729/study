#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
using namespace std;

struct disk{
    int start;
    int worktime;
    disk(int start, int worktime) : start(start), worktime(worktime) {}
};

ostream& operator<<(ostream& os, const disk& d){
    os << "(" << d.start << ", " << d.worktime << ")";
    return os;
}

struct comp{
    bool operator() (disk A, disk B)
    {
        if(A.worktime > B.worktime)
            return true;
        else if(A.worktime == B.worktime)
            return A.start >= B.start;
        return false;
    }
};


int solution(vector<vector<int>> jobs) {
    priority_queue<disk, vector<disk>, comp> q;
    
    int cnt = 0;
    int second = 0;
    int answer = 0;
    
    sort(jobs.begin(),jobs.end());
    while(cnt < jobs.size()){
        while(cnt < jobs.size() && jobs[cnt][0] <= second){
            q.push(disk(jobs[cnt][0], jobs[cnt][1]));
            cnt++;
        }
        
        if(q.empty()){
            second++;
        }
        else{
            cout << q.top();
            second += q.top().worktime;
            answer += second - q.top().start;
            cout << "se : " << second << " answer : " << answer << endl;
            q.pop();
        }
    }
    
    while(!q.empty()){
        cout << q.top();
        second += q.top().worktime;
        answer += second - q.top().start;
        cout << "se : " << second << " answer : " << answer << endl;
        q.pop();
    }
    
    answer /= jobs.size();
    return answer;
}