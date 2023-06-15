#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Element {
    char *s;
    struct Element *next;
    struct Element *prev;
} Element;

typedef struct Daque {
    Element *head;
    Element *tail;
} Daque;

Element *create_element() {
    Element *elem = calloc(1, sizeof(Element));
    elem->next = NULL;
    elem->prev = NULL;
}

Daque *create_daque() {
    Daque *daque = calloc(1, sizeof(Daque));
    daque->head = NULL;
    daque->tail = NULL;
    return daque;
}

void delete_element(Element *elem) {
    free(elem->s);
    free(elem);
}

int daque_delete_from_start(Daque *daque) {
    if (!daque) return 1;
    Element *deleted = daque->head;
    daque->head = deleted->next;
    if (daque->head) daque->head->prev = NULL;
    delete_element(deleted);
    return 0;
}

int daque_delete_from_end(Daque *daque) {
    if (!daque) return 1;
    Element *deleted = daque->tail;
    daque->tail = deleted->prev;
    daque->tail->next = NULL;
    delete_element(deleted);
    return 0;
}

void delete_daque(Daque *daque) {
    if (!daque) return;
    Element *del = daque->head;
    while (del) {
        daque_delete_from_start(daque);
        if (daque->head) del = daque->head;
        else break;
    }
    free(daque);
}

int daque_add_to_end(Daque *daque, char *string) {
    if (!daque) return 1;
    Element *add = create_element();
    add->s = strdup(string);
    if (!daque->head) {
        daque->head = add;
        daque->tail = add;
    } else {
        daque->tail->next = add;
        add->prev = daque->tail;
        daque->tail = add;
    }
    return 0;
}

int daque_add_to_start(Daque *daque, char *string) {
    if (!daque) return 1;
    Element *add = create_element();
    add->s = strdup(string);
    if (!daque->head) {
        daque->head = add;
        daque->tail = add;
    } else {
        add->next = daque->head;
        daque->head->prev = add;
        daque->head = add;
    }
    return 0;
}



int show_from_start(Daque *daque) {
    if (!daque) return 1;
    printf("------------------------\n");
    Element *start = daque->head;
    while (start) {
        printf("%s\n", start->s);
        start = start->next;
    }
    printf("------------------------\n");
    return 0;
}

int show_from_end(Daque *daque) {
    if (!daque) return 1;
    printf("------------------------\n");
    Element *end = daque->tail;
    while (end) {
        printf("%s\n", end->s);
        end = end->prev;
    }
    printf("------------------------\n");
}

int main() {
    Daque *daque = create_daque();
    daque_add_to_end(daque, "HELLO!1");
    daque_add_to_end(daque, "HELLO!2");
    daque_add_to_end(daque, "HELLO!3");
    daque_add_to_end(daque, "HELLO!4");
    daque_add_to_start(daque, "HELLO!5");
    show_from_start(daque);
    daque_delete_from_start(daque);
    show_from_start(daque);
    delete_daque(daque);
    return 0;
}