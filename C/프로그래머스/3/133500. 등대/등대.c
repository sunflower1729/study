#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct node{
    int to;
    struct node* next;
}Node;

typedef Node* pNode;

pNode head[100001] = {0};
int Topology[100001] = {0};

void addNode(int from, int to){
    pNode temp = (pNode)malloc(sizeof(Node));
    temp->to = to;
    temp->next = head[from];
    head[from] = temp;
    Topology[to]++;
    
    pNode temp2 = (pNode)malloc(sizeof(Node));
    temp2->to = from;
    temp2->next = head[to];
    head[to] = temp2;
    Topology[from]++;
}

int visited[100001] = {0};
int will_right_on[100001] = {0};
int light = 0;
int answer = 0;

void print_To(int n){
    for(int i = 1; i <= n; i++){
        printf("%d ", Topology[i]);
    }
    printf("\n");
}

void light_on(int from){ //a번 불 켜짐
    visited[from] = 2;
    pNode temp = head[from];
    
}

void find_one_node(int n){
    int j = n - 1;
    while(j > 0){
        int cnt = 0;
        for(int i = 1; i <= n; i++){
            if(Topology[i] == 1){ // 간선이 1개인 노드
                   
                Topology[i]--;
                pNode temp = head[i];
                int to = temp->to;
                
                while(Topology[to] == 0){
                    temp = temp->next;
                    to = temp->to;
                }
                
                if(Topology[to] != 0) Topology[to]--;
                if(visited[i] == 2)  continue; //이미 불 켜진 노드 그냥 나가
                if(visited[to] == 2){ // 다음 구간이 켜져있어도 그냥 나가
                    continue;
                }
                light_on(to); //불 키러 가기
                answer++;
            }
            if(Topology[i] >= 1) cnt++;
        }
        j = cnt;
    }
}

// lighthouse_rows는 2차원 배열 lighthouse의 행 길이, lighthouse_cols는 2차원 배열 lighthouse의 열 길이입니다.
int solution(int n, int** lighthouse, size_t lighthouse_rows, size_t lighthouse_cols) {
    
    for(size_t i = 0; i < lighthouse_rows; i++){
        addNode(lighthouse[i][0], lighthouse[i][1]);
    }
    
    find_one_node(n);
    return answer;
}