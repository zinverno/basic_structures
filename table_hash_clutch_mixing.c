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
    KeySpace **array;
    int max_size;
    int cur_size;
} Table;

Info *create_info(char *info, int release) {
    Info *inf = calloc(1, sizeof(Info));
    inf->info = strdup(info);
    inf->release = release;
    inf->busy = 1;
    return inf;
}

KeySpace *create_keyspace(char *key, Info *info) {
    KeySpace *space = calloc(1, sizeof(KeySpace));
    space->key = strdup(key);
    space->info = info;
    return space;
}

Table *create_table(int n) {
    Table *table = calloc(1, sizeof(Table));
    table->max_size = n;
    table->array = calloc(n, sizeof(KeySpace *));
    for (int i = 0; i < n; i++) {
        table->array[i] = NULL;
    }
    return table;
}

int hash_func1(int max_size, char *key) {
    return strlen(key) % 2 * 203;
}

int hash_func(int max_size, char *key) {
    int h = hash_func1(max_size, key);
    for (int i = 0; i < strlen(key); i++) {
        h += key[i] * 7 - max_size % key[i];
    }
    h %= max_size;
    return h;
}


int check_release(Table *table, char *key, int hash) {
    KeySpace *space = table->array[hash];
    int rel = 0;
    while (space != NULL) {
        if (space->key)
            if (strcmp(space->key, key) == 0) rel = space->info->release + 1;
        space = space->next;
    }
    return rel;
}

void delete_info(Info *inf) {
    free(inf->info);
    free(inf);
}

void clear(Table *table) {
    KeySpace *prev;
    for (int i = 0; i < table->max_size; i++) {
        KeySpace *space = table->array[i];
        while (space) {
            free(space->key);
            delete_info(space->info);
            prev = space;
            space = space->next;
            free(prev);
        }
    }
    table->cur_size = 0;

}


int table_add(Table *table, char *key, char *info) {
    int hash = hash_func(table->max_size, key);
    int release = check_release(table, key, hash);
    KeySpace *space = table->array[hash];
    if (space) {
        while (space->next) space = space->next;
        space->next = create_keyspace(key, create_info(info, release));
    } else {
        table->array[hash] = create_keyspace(key, create_info(info, release));
        table->cur_size++;
    }
    return 0;
}



Table *perehash(Table *table) {
    int max_size = table->max_size * 2;
    Table *new = create_table(max_size);
    for (int i = 0; i < table->max_size; i++) {
        KeySpace *space = table->array[i];
        while (space) {
            if (space->info->busy == 1) {
                int h = hash_func(max_size, space->key);
                table_add(new, space->key, space->info->info);
                space = space->next;
            }

        }
    }
    clear(table);
    table->max_size = max_size;
    table->array = realloc(table->array, sizeof(KeySpace *) * max_size);
    for (int i = 0; i < max_size; i++) table->array[i] = NULL;
    for (int i = 0; i < max_size; i++) {
        KeySpace *space = new->array[i];
        while (space) {
            table_add(table, space->key, space->info->info);
            space = space->next;
        }
    }
    clear(new);
    free(new->array);
    free(new);
    return 0;
}

int table_add_optic(Table *table, char *key, char *info) {
    if (!table) return 1;
    if (table->max_size == 0) return 1;
    if (table->cur_size > table->max_size / 2) perehash(table);
    table_add(table, key, info);
    return 0;
}

int table_show(Table *table) {
    if (!table) return 1;
    if (!table->array) return 1;
    KeySpace **space = table->array;
    KeySpace *iter;
    for (int i = 0; i < table->max_size; i++) {
        iter = space[i];
        if (iter) {
            printf("%d ---> KEY: %s; INFO: %s; RELEASE: %d; BUSY: %d", i, iter->key, iter->info->info,
                   iter->info->release,
                   iter->info->busy);
            while (iter->next) {
                printf(" ---> ");
                printf("KEY: %s; INFO: %s; RELEASE: %d; BUSY: %d", iter->key, iter->info->info, iter->info->release,
                       iter->info->busy);
                iter = iter->next;
            }
            printf("\n");
        }
    }


    return 0;
}

int table_delete(Table *table, char *key) {
    if (!table) return 1;
    if (!table->array) return 1;
    int h = hash_func(table->max_size, key);
    KeySpace *space = table->array[h];
    while (space->key) {
        if (strcmp(space->key, key) == 0 && space->info->busy == 1) {
            space->info->busy = 0;
            break;
        } else space = space->next;
    }
    return 0;
}

int main() {
    Table *table = create_table(3);
    table_add_optic(table, "a", "dgdf");
    table_add_optic(table, "asdfdfg", "dgdf");
    table_add_optic(table, "b", "b");
    table_show(table);
    clear(table);
    free(table->array);
    free(table);
    return 0;
}