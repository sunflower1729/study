#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int N, M;

typedef struct Node {
    int to;
    int value;
    struct Node* next;
}Node;

typedef Node* pNode;
pNode Head[1001] = { 0 };
void addV(int p, int q, int r) {
    pNode temp = (pNode)malloc(sizeof(Node));
    if (temp == NULL) {
        exit(1);
    }
    temp->to = q;
    temp->value = r;
    temp->next = Head[p];
    Head[p] = temp;
}

int pre_visit[1001] = { 0 };
int visit[1001] = { 0 };
int queue[1000*1000 + 1] = { 0 };

void find_route() {
    int front = 0, rear = -1;
    queue[++rear] = 1;
    while (front <= rear) {
        int t = queue[front++];
        pNode temp = Head[t];
        while (temp != NULL) {
            int to = temp->to;
            int value = temp->value;
            if (visit[to] < visit[t] + value) {
                visit[to] = visit[t] + value;
                pre_visit[to] = t;
                if (to == 1) {
                    temp = temp->next;
                    continue;
                }
                queue[++rear] = to;
            }
            temp = temp->next;
        }
    }
    
    int next = pre_visit[1];
    int pnt = 1;
    int answer[1000] = { 1, };
    while (next != 1) {
        answer[pnt++] = next;
        next = pre_visit[next];
    }
    answer[pnt++] = next;
    printf("%d\n", visit[1]);
    for (int i = pnt - 1; i >= 0; i--) {
        printf("%d ", answer[i]);
    }
}


int main() {
    (void)scanf("%d", &N);
    (void)scanf("%d", &M);
    for (int i = 0; i < M; i++) {
        int p, q, r;
        (void)scanf("%d %d %d", &p, &q, &r);
        addV(p, q, r);
    }
    find_route();
}