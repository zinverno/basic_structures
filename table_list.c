#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Info {
    char *info;
    int release;
    int busy;
} Info;

typedef struct KeySpace {
    char *key;
    Info *info;
    struct KeySpace *next;
} KeySpace;

typedef struct Table {
    KeySpace *head;
} Table;

void delete_info(Info *info) {
    free(info->info);
    free(info);
}

void delete_keyspace(KeySpace *space) {
    delete_info(space->info);
    free(space->key);
    free(space);
}

int delete_table(Table *table) {
    if (!table) return 1;
    if (!table->head) return 1;
    KeySpace *prev;
    while (table->head) {
        prev = table->head;
        table->head = table->head->next;
        delete_keyspace(prev);
    }
    free(table);
    return 0;
}

Info *create_info(char *info, int release) {
    Info *inf = calloc(1, sizeof(Info));
    inf->info = strdup(info);
    inf->release = release;
    inf->busy = 1;
    return inf;
}

KeySpace *create_keyspace(char *element, char *info, int release) {
    KeySpace *space = calloc(1, sizeof(KeySpace));
    space->key = strdup(element);
    space->next = NULL;
    space->info = create_info(info, release);
    return space;
}

Table *create_table() {
    Table *table = calloc(1, sizeof(Table));
    table->head = NULL;
    return table;
}

int check_release(Table *table, char *key, int *release) {
    if (!table) return 1;
    if (!table->head) {
        (*release) = 0;
        return 0;
    }
    KeySpace *checking = table->head;
    do {
        if (strcmp(checking->key, key) == 0) (*release)++;
        checking = checking->next;
    } while (checking);
    return 0;
}

KeySpace *getting_last(Table *table) {
    KeySpace *space = table->head;
    while (space->next) {
        space = space->next;
    }
    return space;
}



int table_delete(Table *table, char *key) {
    if (!table) return 1;
    if (!table->head) return 1;
    KeySpace *element = table->head;
    while(strcmp(element->key, key) != 0 || element->info->busy == 0) {
        element = element->next;
        if (element == NULL) break;
    }
    if (element != NULL) {
        element->info->busy = 0;
    }
    return 0;
}

int table_add(Table *table, char *key, char *info) {
    if (!table) return 1;
    int release = 0;
    check_release(table, key, &release);
    KeySpace *space = create_keyspace(key, info, release);
    if (table->head == NULL) table->head = space;
    else {
        KeySpace *last = getting_last(table);
        last->next = space;
    }
    return 0;
}

int table_show(Table *table) {
    printf("TABLE:\n");
    if (!table) return 1;
    if (!table->head) return 1;
    KeySpace *space = table->head;
    int elem = 1;
    while(space) {
        printf("%d ---> key = %s; info = %s; release = %d; busy = %d\n", elem, space->key, space->info->info, space->info->release, space->info->busy);
        space = space->next;
        elem++;
    }
    return 0;
}

int main() {
    Table *table = create_table();
    table_add(table, "1", "1");
    table_add(table, "3", "1");
    table_add(table, "4", "1");
    table_add(table, "5", "1");
    table_add(table, "4", "1");
    table_add(table, "1", "1");
    table_add(table, "1", "1");
    table_delete(table, "1");
    table_delete(table, "1");
    table_delete(table, "1");
    table_delete(table, "4");
    table_show(table);
    delete_table(table);

}
