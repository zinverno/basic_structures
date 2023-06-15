#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Element {
    char *str;
} Element;

typedef struct Queue {
  int head;
  int tail;
  int cur_size;
  int max_size;
  Element *elem;
} Queue;

Element *create_element(int n) {
    Element *elem = calloc(n, sizeof(Element));
    return elem;
}

Queue *create_queue (int n) {
    Queue *ans = calloc(1, sizeof(Queue));
    ans->head = 0;
    ans->tail = 0;
    ans->cur_size = 0;
    ans->max_size = n;
    ans->elem = create_element(n);
    return ans;
}

int delete_queue(Queue *queue) {
    for (int i = 0; i < queue->max_size; i++) {
        if (queue->elem[i].str) free(queue->elem[i].str);
    }
    free(queue->elem);
    free(queue);
}

int queue_add(Queue *queue, char *element) {
    if (queue->cur_size == queue->max_size) {
        return 1; // Очередь переполнена
    }
    queue->elem[queue->tail].str = strdup(element);
    queue->tail = (queue->tail + 1) % queue->max_size;
    queue->cur_size++;
    return 0;
}

int queue_pop(Queue *queue) {
    if (queue->cur_size == 0) {
        return 1; // Очередь пустая
    }
    printf("%s\n", queue->elem[queue->head].str);
    free(queue->elem[queue->head].str);
    queue->head = (queue->head + 1) % queue->max_size;
    queue->cur_size--;
}

int queue_show(Queue *queue) {
    if (!queue) return 1;
    if (queue->cur_size == 0) return 1;
    printf("---------------------------\n");
    int head = queue->head;
    int tail = queue->tail;
    do {
        printf("%s\n", queue->elem[head].str);
        head = (head + 1) % queue->max_size;
    } while (head != tail);
    printf("---------------------------\n");
    return 0;
}

int main() {
    Queue *queue = create_queue(4);
    queue_add(queue, "He.");
    queue_add(queue, "Hi.");
    queue_add(queue, "How are you.");
    queue_add(queue, "I am fine.");
    queue_show(queue);
    queue_pop(queue);
    queue_show(queue);
    queue_add(queue, "Hello.");
    queue_show(queue);
    delete_queue(queue);

    return 0;

}