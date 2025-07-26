#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
/*
노드생성
노드 번호
자식 숫자
자식 노드 주소

입력값이 -1이면 연결 안함
입력값이 있으면 그 번호를 해당 부모 노드 밑에 생성

쭉쭉쭉

마지막에 입력값이 -1로 들어왔던 노드들 돌기

쭉 돌다가 삭제 노드 번호가 나오면 거기는 제외
child가 없는 것들 번호 세기
*/

typedef struct node {
    int num;
    int child_cnt;
    struct node* child[51];
}Node;

Node tree[51] = { 0 };

int N;
int erase;

int root[51] = { 0 };
int root_cnt = 0;


int answer = 0;
void find_leafnode(int node, int root_node) {
    if(node == erase){ //root가 지워진 값인 경우 그냥 retrun;
        return;
    }
    if (tree[node].child_cnt == 0) {
        answer++;
        return;
    }
    for (int i = 0; i < tree[node].child_cnt; i++) {
        if (tree[node].child[i]->num == erase) { //자식 노드 중에서 erase값을 발견
            if(tree[node].child_cnt == 1){      //erase를 가진 부모가 그 자식밖에 없을 경우 leafnode
                answer++;
                return;
            }
            continue;
        }
        find_leafnode(tree[node].child[i]->num, root_node);
    }
}

void circuit_root() {
    for (int i = 0; i < root_cnt; i++) {
        find_leafnode(root[i], root[i]);
    }
}

int main() {
    (void)scanf(" %d", &N);
    for (int i = 0; i < N; i++) {
        int parent;
        (void)scanf(" %d", &parent);
        if (parent == -1) {
            root[root_cnt++] = i;
            continue;
        }
        tree[parent].child[tree[parent].child_cnt++] = &tree[i];
        tree[i].num = i;
    }
    (void)scanf(" %d", &erase);
    circuit_root();
    printf("%d", answer);
}