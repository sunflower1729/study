#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX 1000

// map과 route 모두 MAX + 2로 통일 (1-indexed 사용을 고려하여 넉넉하게)
int map[MAX + 2][MAX + 2] = { 0 };
int n, m;

int dx[] = { 1, -1, 0, 0 };
int dy[] = { 0, 0, 1, -1 };

// 불의 전파 시간을 저장하는 배열. -1은 불이 도달하지 않은 칸
int fire_time[MAX + 2][MAX + 2] = { 0 };
// 지훈이의 이동 시간을 저장하는 배열. -1은 지훈이가 도달하지 않은 칸
int jh_time[MAX + 2][MAX + 2] = { 0 };

typedef struct queue {
	int x;
	int y;
	int value;
}Queue;

Queue q[1000000 + 1]; // 큐 크기도 넉넉하게 +1
int front = 1, rear = 1;

// (생략: print_map, print_route 함수 - 디버깅용이므로 실제 제출 시에는 필요없음)

// fire_time과 jh_time 배열을 -1로 초기화하는 함수
void init_times() {
	for (int i = 0; i <= n + 1; i++) {
		for (int j = 0; j <= m + 1; j++) {
			fire_time[i][j] = -1;
			jh_time[i][j] = -1;
		}
	}
}

void push(Queue q1) {
	q[rear++] = q1;
}

Queue pop() {
	return q[front++];
}

int isempty() {
	return front == rear;
}

// 불 확산 BFS
void fire_bfs() {
	while (!isempty()) {
		Queue temp = pop();
		int current_time = temp.value;

		for (int i = 0; i < 4; i++) {
			int nx = temp.x + dx[i];
			int ny = temp.y + dy[i];

			// 미로 경계 밖으로 벗어나는 경우 (불은 격자 내에서만 의미 있음)
			if (nx < 1 || nx > m || ny < 1 || ny > n)
				continue;

			// 벽이거나 이미 불이 도달한 경우 (더 빠른 시간에)
			if (map[ny][nx] == 1 || fire_time[ny][nx] != -1)
				continue;

			// 불이 이미 시작 지점인 경우는 0으로 초기화되었으니 여기서는 current_time + 1
			fire_time[ny][nx] = current_time + 1;
			push((Queue) { nx, ny, current_time + 1 });
		}
	}
}

// 지훈이 이동 BFS
int find_exit() {
	while (!isempty()) {
		Queue temp = pop();
		int x = temp.x;
		int y = temp.y;
		int current_time = temp.value; // 지훈이가 현재 위치에 도달한 시간

		// 지훈이가 다음 칸으로 이동하여 탈출하는 경우를 먼저 고려
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];

			// 미로 경계 밖으로 이동 시도 (탈출 성공)
			// 이때 중요한 것은, '현재 칸에서 다음 칸으로 이동하는 시점'에 불이 그 다음 칸에 도달했는지 여부
			// 즉, (current_time + 1) 시점에 (nx, ny)에 불이 없어야 함.
			if (nx < 1 || nx > m || ny < 1 || ny > n) {
				// 불이 아직 해당 위치에 도달하지 않았거나, 지훈이가 불보다 먼저 도달
				if (fire_time[y][x] == -1 || fire_time[y][x] > current_time) {
					return current_time + 1; // 탈출 성공 시간 반환 (움직인 횟수 + 1)
				}
				// 이 경우 불에 갇혀 탈출 불가능하므로 이 경로는 유효하지 않음
				continue;
			}

			// 벽인 경우 이동 불가
			if (map[ny][nx] == 1)
				continue;

			// 지훈이가 이미 방문했거나 더 빠른 경로로 방문한 경우
			if (jh_time[ny][nx] != -1)
				continue;

			// 불이 (nx, ny) 칸에 도달하는 시간과 지훈이가 (nx, ny) 칸에 도달하려는 시간을 비교
			// 불이 먼저 도달했거나 동시에 도달하는 경우 지훈이는 그 칸으로 갈 수 없음
			if (fire_time[ny][nx] != -1 && fire_time[ny][nx] <= current_time + 1)
				continue;

			// 이동 가능한 경우 큐에 추가 및 방문 시간 기록
			push((Queue) { nx, ny, current_time + 1 });
			jh_time[ny][nx] = current_time + 1;
		}
	}
	return -1; // 탈출 불가능
}

int main() {
	(void)scanf("%d %d", &n, &m);

	Queue JH_start = { 0, 0, 0 }; // 지훈이 시작 위치
	init_times(); // fire_time과 jh_time 모두 -1로 초기화

	for (int i = 1; i <= n; i++) { // y
		for (int j = 1; j <= m; j++) { // x
			char ch;
			(void)scanf(" %c", &ch);
			switch (ch) {
			case '#':
				map[i][j] = 1; // 벽
				break;
			case 'J':
				JH_start = (Queue){ j, i, 0 }; // 지훈이 시작 위치
				jh_time[i][j] = 0; // 지훈이 시작 시간 0
				break;
			case 'F':
				push((Queue) { j, i, 0 }); // 불 시작 위치 큐에 삽입
				fire_time[i][j] = 0; // 불 시작 시간 0
				break;
			case '.':
				map[i][j] = 0; // 빈 공간
				break;
			}
		}
	}

	// 불 BFS 실행
	fire_bfs();

	// 지훈이 BFS를 위해 큐 초기화 및 지훈이 시작 위치 삽입
	front = 1;
	rear = 1;
	push(JH_start);

	// 지훈이 BFS 실행 및 결과 저장
	int answer = find_exit();

	if (answer == -1)
		printf("IMPOSSIBLE\n"); // IMPOSSIBLE 뒤에 개행 문자 추가
	else
		printf("%d\n", answer); // 올바른 최종 시간 출력 및 개행 문자 추가
}