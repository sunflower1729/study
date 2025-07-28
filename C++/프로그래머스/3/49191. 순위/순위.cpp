#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

typedef struct Player {
    vector<int> match_win;
    vector<int> match_lose;
} Player;

Player player[101];
bool visited[101];

// DFS로 이긴 사람 수 구하기
int count_win(int start) {
    int count = 0;
    for (int next : player[start].match_win) {
        if (!visited[next]) {
            visited[next] = true;
            count++;
            count += count_win(next);
        }
    }
    return count;
}

// DFS로 진 사람 수 구하기
int count_lose(int start) {
    int count = 0;
    for (int next : player[start].match_lose) {
        if (!visited[next]) {
            visited[next] = true;
            count++;
            count += count_lose(next);
        }
    }
    return count;
}

int solution(int n, vector<vector<int>> results) {
    
    for (auto result : results) {
        int win = result[0];
        int lose = result[1];
        player[win].match_win.push_back(lose);
        player[lose].match_lose.push_back(win);
    }

    int answer = 0;
    for (int i = 1; i <= n; ++i) {
        memset(visited, false, sizeof(visited));
        visited[i] = true;
        int win_cnt = count_win(i);

        memset(visited, false, sizeof(visited));
        visited[i] = true;
        int lose_cnt = count_lose(i);

        if (win_cnt + lose_cnt == n - 1)
            answer++;
    }

    return answer;
}
