#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Element {
    char *data;
    struct Element *next;
} Element;
typedef struct Queue{
    struct Element *head, *tail;
} Queue;
char *getStr(){
    char *ans = malloc(sizeof(char));
    char n;
    int len = 0;
    n = getchar();
    while(n != EOF && n != '\n'){
        ans = realloc(ans, sizeof(char) * (len + 2));
        ans[len] = n;
        len += 1;
        n = getchar();
    }
    ans[len] = '\0';
    return ans;
}
void init(Queue *queue){
    queue->head = NULL;
    queue->tail = NULL;
}
Element *createNode(char *el){
    Element *tmp = malloc(sizeof(Element));
    tmp ->next = NULL;
    tmp->data = strdup(el);
    return tmp;
}
char *pop(Queue *queue){
    if (queue->head == NULL && queue->tail == NULL){
        return NULL; //Пусто
    }
    Element *tmp = queue->head;
    queue->head = queue->head->next;
    char *el = strdup(tmp->data);
    free(tmp->data);
    free(tmp);
    return el;
}
void push(Queue *queue, char *el){
    if (queue->head == NULL && queue->tail == NULL){
        Element *tmp = createNode(el);
        queue->head = tmp;
        queue->tail = tmp;
    }
    else{
        queue->tail->next = createNode(el);
        queue->tail = queue->tail->next;
    }
}
void show(Queue *queue){
    Element *ptr = queue->head;
    while (ptr){
        printf("%s ", ptr->data);
        ptr = ptr->next;
    }
}
void clear(Queue *queue){
    while (queue->head){
 	Element *tmp = queue->head;
    	queue->head = queue->head->next;
    	free(tmp->data);
    	free(tmp);
    }
    free(queue);
}
int main() {
    Queue *queue = malloc(sizeof(Queue));
    init(queue);
    int n;
    scanf("%d ", &n);
    for (int i = 0; i < n; i++){
        char *el = getStr();
        push(queue, el);
        free(el);
    }
    printf("\n");
    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; i++){
        char *el = pop(queue);
        printf("%s ", el);
        free(el);
    }
    printf("\n");
    show(queue);
    clear(queue);
}

