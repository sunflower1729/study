#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
    char name[16];
    struct Node* next;
    struct Node* child;
}Node;

typedef Node* pNode;

pNode add_Node(pNode parents, pNode chi){
    if(parents->child == NULL){
        parents->child = chi;
        return chi;
    }

    pNode temp1 = NULL;
    pNode temp2 = parents->child;

    while(temp2 != NULL){
        int cmp = strcmp(temp2->name, chi->name);
        if(cmp == 0){
            free(chi);
            return temp2;
        }
        if(cmp > 0){
            if(temp1 == NULL){
                parents->child = chi;
                chi->next = temp2;
            }
            else{
                temp1->next = chi;
                chi->next = temp2;
            }
            return chi;
        }
        temp1 = temp2;
        temp2 = temp2->next;
    }

    temp1->next = chi;
    return chi;
}

void print_Node(pNode parent, int depth){
    if(depth >= 0){
        for(int i = 0; i < depth; ++i) 
            printf("--");
        printf("%s\n", parent->name);
    }
    pNode temp = parent->child;
    while(temp != NULL){
        print_Node(temp, depth + 1);
        temp = temp->next;
    }
}

int main(){
    pNode root = (pNode)malloc(sizeof(Node));
    strcpy(root->name, "");
    root->child = NULL;
    root->next = NULL;

    int N;
    (void)scanf("%d", &N);

    for(int i = 0; i < N; i++){
        int K;
        (void)scanf("%d", &K);
        pNode parent = root;
        for(int j = 0; j < K; j++){
            char chi[16];
            (void)scanf(" %15s", &chi);
            
            pNode temp = (pNode)malloc(sizeof(Node));
            strcpy(temp->name, chi);
            temp->child = NULL;
            temp->next = NULL;
            parent = add_Node(parent, temp);
        }
    }

    print_Node(root, -1);
}