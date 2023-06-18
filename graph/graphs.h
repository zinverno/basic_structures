//
// Created by tamerlan on 18.06.23.
//

#ifndef BASIC_STRUCTURES_GRAPHS_H
#define BASIC_STRUCTURES_GRAPHS_H
typedef struct Vertex {
    char* name;
    int dist;
    struct Vertex* next;
} Vertex;
typedef struct Graph {
    int vertexCount;
    Vertex **vertices;
} Graph;
typedef struct Node{
    int a;
    struct Node* next;
}Node;
typedef struct Queue{
    Node* start;
    Node* end;
}Queue;
int* Bellman_Ford_Algorithm(Graph* graph,char* namefr);
void add_Edge(Graph* graph,char* to,char* from,int dist);
void add_Vertex(Graph* graph,char* key);
#endif //BASIC_STRUCTURES_GRAPHS_H
