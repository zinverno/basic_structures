#include "stdio.h"
#include "stdlib.h"
#include "string.h"


typedef struct Element {
    char *string;
    struct Element *next;
} Element;

typedef struct Stack {
    Element *head;
} Stack;


Element *create_element(char *element) {
    Element *elem = calloc(1, sizeof(Element));
    elem->next = NULL;
    elem->string = strdup(element);
    return elem;
}

Stack *create_stack() {
    Stack *ans = calloc(1, sizeof(Stack));
    return ans;
}

int delete_elem(Element *elem) {
    free(elem->string);
    free(elem);
}

int stack_del(Stack *stack) {
    Element *elem = stack->head;
    stack->head = stack->head->next;
    delete_elem(elem);
}

int delete_stack(Stack *stack) {
    Element *elem = stack->head;
    while (stack->head) {
        stack_del(stack);
    }
    free(stack);
}


int stack_add(Stack *stack, char *element) {
    Element *add = create_element(element);
    if (!stack->head) {
        stack->head = add;
    } else {
        Element *prev = stack->head;
        stack->head = add;
        stack->head->next = prev;
    }
    return 1;
}

int stack_print_last(Stack *stack) {
    if (stack->head) {
        printf("%s\n", stack->head->string);
        return 0;
    }
    return 1;
}

int stack_show(Stack *stack) {
    printf("-------------------------------\n");
    if (!stack->head) return 1;
    Element *elem = stack->head;
    while (elem) {
        printf("%s\n", elem->string);
        elem = elem->next;
    }
    printf("-------------------------------\n");
    return 0;
}



int main() {
    Stack *stack = create_stack();
    stack_add(stack, "Hello.");
    stack_add(stack, "Hi.");
    stack_add(stack, "How are you.");
    stack_add(stack, "I am fine.");
    stack_add(stack, "That is good.");
    stack_show(stack);
    stack_del(stack);
    stack_show(stack);
    delete_stack(stack);
    return 0;
}
