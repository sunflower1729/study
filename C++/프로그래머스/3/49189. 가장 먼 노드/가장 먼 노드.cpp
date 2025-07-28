#include <string>
#include <vector>
#include <iostream>
// 모든 간선 양방향 연결
// 해당 노드에서 연결된 노드로 가는 함수 생성 // 입력 벡터
// visit를 표시해 갔던 곳 다시 못가게.
// 새로운 노드를 벡터에 추가 
// 벡터를 다시 함수 돌리기.
// 새로 추가되는게 없으면 끝

using namespace std;

typedef struct node{
    vector<int> v;
}Node;

Node graph[20001];
int visit[20001];

int fine_root(){
    vector<int> root1;
    root1.push_back(1);
    visit[1] = 1;
    int answer;
    while(root1.size() > 0){
        answer = root1.size();
        vector<int> root2;
        for(auto r : root1){
            for(auto newnode : graph[r].v){
                if(visit[newnode]) continue;
                //cout << newnode << endl;
                root2.push_back(newnode);
                visit[newnode] = 1;
            }
        }
        root1 = root2;
    }
    return answer;
}

int solution(int n, vector<vector<int>> edge) {
    for(auto e : edge){
        graph[e[0]].v.push_back(e[1]);
        graph[e[1]].v.push_back(e[0]);
    }
    
    int answer = fine_root();
    
    return answer;
}