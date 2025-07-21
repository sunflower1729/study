#include<vector>
#include<queue>
#include<iostream>
using namespace std;

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

int solution(vector<vector<int> > maps)
{
    vector<vector<int>> visit(maps.size(), vector<int>(maps[0].size(), 0));
    int answer = -1;
    
    queue<pair<int, int>> q;
    q.push({0, 0});
    visit[0][0] = 1;
    
    while(!q.empty()){
        int y = q.front().first;
        int x = q.front().second;
        q.pop();
        if(y == maps.size() - 1 && x == maps[0].size() - 1)
            return visit[y][x];
        for(int i = 0; i < 4; i++){
            int nx = x + dx[i];
            int ny = y + dy[i];
            
            if(nx < 0 || ny < 0 || nx >= maps[0].size() || ny >= maps.size()) continue;
            if(maps[ny][nx] == 0) continue;
            if (visit[ny][nx] != 0) continue;
            visit[ny][nx] = visit[y][x] + 1;
            q.push({ny, nx});
            
        }
    }
    
    return answer;
}