//
// Created by tamerlan on 18.06.23.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include "graphs.h"
void add_queue(Queue *queue, int j) {
    Node *node = calloc(1, sizeof(Node));
    node->a = j;
    if (queue->end == NULL) {
        queue->start = node;
        queue->end = node;
    } else {
        queue->end->next = node;
        queue->end = node;
    }
}

int del_queue(Queue *queue) {
    Node *node = queue->start;
    int k = node->a;
    if (queue->start == queue->end) {
        queue->start = NULL;
        queue->end = NULL;
    } else {
        queue->start = node->next;
    }
    free(node);
    return k;
}
void add_Vertex(Graph* graph,char* key){
    graph->vertices=realloc(graph->vertices,(graph->vertexCount+1)* sizeof(Vertex));
    Vertex *ins= calloc(1, sizeof(Vertex));
    ins->name=key;
    graph->vertices[graph->vertexCount]=ins;
    graph->vertexCount++;
}
int fintoGraph(Graph *graph, char *name) {
    for (int i = 0; i < graph->vertexCount; ++i) {
        if (strcmp(graph->vertices[i]->name, name) == 0) {
            return i;
        }
    }
    return -1;
}
void addNode(Vertex *head, Vertex *new) {
    Vertex *ptr = head;
    while (ptr->next) {
        ptr = ptr->next;
    }
    ptr->next = new;
}

void add_Edge(Graph* graph,char* to,char* from,int dist){
    if(fintoGraph(graph, from) == -1 || fintoGraph(graph, to) == -1){
        perror("Одной или двух вершин нет в графе");
        return;
    }
    Vertex *vertn= calloc(1, sizeof(Vertex));
    vertn->name=from;
    vertn->dist=dist;
    Vertex *from1 = graph->vertices[fintoGraph(graph, to)];
    addNode(from1,vertn);
}
void BFS(Graph* graph,char* sname,char* tname){
    int n=graph->vertexCount;
    int color[n];
    Vertex* pred[n];
    int dist[n];
    Queue * deq= calloc(1, sizeof(Queue));
    for (int i = 0; i < n; ++i) {
        color[i]=0;
        dist[i]=INT_MAX;
        pred[i]=NULL;
    }
    int s= fintoGraph(graph,sname);
    if(s==-1){
        perror("Нет такой вершины в графе");
        return;
    }
    color[s]=1;
    dist[s]=0;
    add_queue(deq,s);
    while(deq->start){
        Vertex *ptr = graph->vertices[s];
        ptr=ptr->next;
        while(ptr){
            int k= fintoGraph(graph,ptr->name);
            if(color[k]==0){
                color[k]=1;
                dist[k]=dist[s]+1;
                pred[k]=graph->vertices[s];
                add_queue(deq,k);
            }
            ptr=ptr->next;
        }
        color[s]=2;
    }
    while ((deq->start)) {
        int k = del_queue(deq);
        char *str = graph->vertices[k]->name;
        printf("%s\n", str);
    }
    return ;
}
//void DFS(Graph* graph){
//    int n=graph->vertexCount;
//    int color[n];
//    Vertex* pred[n];
//    int d[n];
//    int f[n];
//    int time=0;
//    for (int i = 0; i < n; ++i) {
//        color[i]=0;
//        pred[i]=NULL;
//    }
//    for (int i = 0; i < n; ++i) {
//        if(color[i]==0){
//            DFS_Visit
//        }
//    }
//}
int sum(int a,int b){
    if(a==INT_MAX){
        if(b==INT_MIN){
            return 0;
        }else{
            return INT_MAX;
        }
    }else if(b==INT_MAX){
        if(a==INT_MIN){
            return 0;
        }else{
            return INT_MAX;
        }
    }else if(a==INT_MIN || b==INT_MIN){
        return INT_MIN;
    }
    return a+b;
}
int* Bellman_Ford_Algorithm(Graph* graph,char* namefr){
    int s= fintoGraph(graph,namefr);
    int n=graph->vertexCount;
    int* dist= calloc(n, sizeof(int));
    Vertex* pred[n];
    for (int i = 0; i < n; ++i) {
        dist[i]=INT_MAX;
        pred[i]=NULL;
    }
    dist[s]=0;
    for (int k = 0; k < n-1; ++k) {
        for (int i = 0; i < n; ++i) {
            Vertex* ptr=graph->vertices[i]->next;
            while(ptr){
                int j= fintoGraph(graph,ptr->name);
                if(dist[j]>sum(dist[i],ptr->dist)){
                    dist[j]=dist[i]+ptr->dist;
                    pred[j]=graph->vertices[i];
                }
                ptr=ptr->next;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        Vertex* ptr=graph->vertices[i]->next;
        while(ptr){
            int j= fintoGraph(graph,ptr->name);
            if(dist[j]>sum(dist[i],ptr->dist)){
                return NULL;
            }
            ptr=ptr->next;
        }
    }
    return dist;
}
