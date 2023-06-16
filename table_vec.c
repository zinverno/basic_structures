#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define N 100
typedef struct Info{
    char* info;
    int release;
    int busy;
}Info;
typedef struct KeySpace{
char * key;
Info* info;
}KeySpace;
typedef struct Table{
KeySpace * ks[N];
int n;
}Table;
Table *create_table() {
    return calloc(1, sizeof(Table));
}

int find_last(Table *table, char *key) {
    int rel = 1;
    for (int i = 0; i < table->n; ++i) {
        if (table->ks[i]->info->busy == 1 && strcmp(key, table->ks[i]->key) == 0) {
            rel++;
        }
    }
    return rel;
}

int find_first(Table *table, char *key) {
    for (int i = 0; i < table->n; ++i) {
        if (table->ks[i]->info->busy == 1 && strcmp(key, table->ks[i]->key) == 0) {
            return i;
        }
    }
    return -1;
}

int find_ver(Table *table, char *key, int ver) {
    for (int i = 0; i < table->n; ++i) {
        if (table->ks[i]->info->busy == 1 && strcmp(key, table->ks[i]->key) == 0 &&
            table->ks[i]->info->release == ver) {
            return i;
        }
    }
    return -1;
}

int find_table_all(Table *table, char *key) {
    for (int i = 0; i < table->n; ++i) {
        if (table->ks[i]->info->busy == 1 && strcmp(key, table->ks[i]->key) == 0) {
            printf("%s", table->ks[i]->info->info);
        }
    }
    return 0;
}

char *find_table_vers(Table *table, char *key, int ver) {
    for (int i = 0; i < table->n; ++i) {
        if (table->ks[i]->info->busy == 1 && strcmp(key, table->ks[i]->key) == 0 &&
            table->ks[i]->info->release == ver) {
            return table->ks[i]->info->info;
        }
    }
    return NULL;
}

int garbage_collector(Table *table) {
    int i = 0;
    int j = 0;

}

KeySpace *make_ks(char *key, char *info) {
    KeySpace *ks = calloc(1, sizeof(KeySpace));
    ks->info = calloc(1, sizeof(Info));
    ks->info->info = info;
    ks->key = key;
    return ks;
}

int add_table(Table *table, char *key, char *info) {
    if (table->n + 1 <= N) {
        table->ks[table->n] = make_ks(key, info);
        table->ks[table->n]->info->busy = 1;
        table->ks[table->n]->info->release = find_last(table, key);
        table->n++;
    } else {
        garbage_collector(table);
        if (table->n + 1 <= N) {
            perror("overflow");
            return 1;
        }
        table->ks[table->n]->key = key;
        table->ks[table->n]->info->info = info;
        table->ks[table->n]->info->busy = 1;
        table->ks[table->n]->info->release = find_last(table, key);
    }
    return 0;
}

/*  удаление с чисткой мусора   */

int del_table_ver(Table *table, char *key, int ver) {
    int rel = find_last(table, key);
    if (rel == 0) {
        return 1;
    }
    int ind = find_ver(table, key, ver);
    free(table->ks[ind]->info->info);
    free(table->ks[ind]->key);
    free(table->ks[ind]);
    free(table->ks[ind]->info);
    table->ks[ind]->info->busy = 0;
    return 0;
}

int del_table_all(Table *table, char *key) {
    int rel = find_last(table, key);
    if (rel == 0) {
        return 1;
    }
    int i = 1;
    while (del_table_ver(table, key, i) != 1) {
        i++;
    }
    return 0;
}

/* удаление когда мы ставим последний момент на место удаленного */
int del_table_ver_(Table *table, char *key, int ver) {
    int rel = find_last(table, key);
    if (rel == 0) {
        return 1;
    }
    int ind = find_ver(table, key, ver);
//    free(table->ks[ind]->info->info);
//    free(table->ks[ind]->key);
    table->ks[ind]->info->info = table->ks[table->n - 1]->info->info;
    table->ks[ind]->info->release = table->ks[table->n - 1]->info->release;
    table->ks[table->n - 1]->info->info=NULL;
    table->ks[ind]->key = table->ks[table->n - 1]->key;
    table->ks[table->n - 1]->key=NULL;
    table->n--;
    return 0;
}

int del_table_all_(Table *table, char *key) {
    int rel = find_last(table, key);
    if (rel == 0) {
        return 1;
    }
    int i = 1;
    while (del_table_ver_(table, key, i) != 1) {
        i++;
    }
    return 0;
}

int show_table(Table *table) {
    printf("Table:\n");
    for (int i = 0; i < table->n; ++i) {
        printf("Elem %d:\n", i + 1);
        printf("Key:%s\nInfo:%s\nver:%d\n", table->ks[i]->key, table->ks[i]->info->info);
    }
    return 0;
}

int free_table(Table *table) {
    for (int i = 0; i < table->n; ++i) {
        free(table->ks[i]->info->info);
        free(table->ks[i]->key);
        free(table->ks[i]->info);
        free(table->ks[i]);
    }
    free(table);
}
int main() {
    Table* table=create_table();
    add_table(table,"bebra","bebra1");
    add_table(table,"bebra","bebra2");
    add_table(table,"bebra","bebra3");
    add_table(table,"bebra","bebra4");
    del_table_ver_(table,"bebra",2);
    show_table(table);
    return 0;
}

