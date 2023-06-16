#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 11

typedef struct Item{
    char *element;
}Item;

typedef struct KeySpace{
    Item *info;
    char *key;
    int busy;
    int release;
}KeySpace;

typedef struct Table{
    KeySpace *ks;
    int msize;
}Table;

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

int getInt(){
    int n, a;
    do{
        n = scanf("%d", &a);
        if (n < 0){
            return 0;
        }
        if (n == 0 || a < 0){
            printf("Введен некоректный символ, повторите попытку:\n");
            scanf("%*[^\n]");
            scanf("%*c");
        }
    }while(n == 0 || a < 0);
    scanf("%*[^\n]");
    scanf("%*c");
    return a;
}

int hash1(char *str, Table *board){
    int i = 0;
    for (int j = 0; j < strlen(str) / 3; j++){
        i += str[j] * 3;
    }
    for (int j = 0; j < strlen(str)/2; j++){
        i += str[j] * 2;
    }
    for (int j = 0; str[j]; j++){
        i += str[j];
    }
    return i % board->msize;
}

int hash2(char *str, Table *board) {
    int i = 0;
    for (int j = 0; str[j]; j++){
        i += str[j];
    }
    return i % (board->msize - 1) + 1;
}

int count_rel(Table *board, char *key){
    int i = 0;
    int rel = 0;
    while (i < board->msize){
        int h = (hash1(key, board) + i * hash2(key, board))%board->msize;
        if ( board->ks[h].busy != 0 && strcmp(board->ks[h].key, key) == 0){
            rel += 1;
        }
        i += 1;
    }
    return rel;
}

int Add(Table *board, char *key, char *el){
    int k = 0;
    int r = count_rel(board, key);
    while (k < board->msize){
        int h = (hash1(key, board) + k * hash2(key, board)) % board->msize;
        if (board->ks[h].busy == 0){
            board->ks[h].info = malloc(sizeof(Item));
            board->ks[h].info->element = strdup(el);
            board->ks[h].key = strdup(key);
            board->ks[h].release = r + 1;
            board->ks[h].busy=1;
            return 1; //все ок
        }
        k += 1;
    }
    return 0; //ошибка
}

int Delete(Table *board, char *key){
    int k = 0;
    int r = count_rel(board, key);
    if (r == 0){
        return 0; //ошибка
    }
    printf("Всего %d версий. Какую хотите удалить? 0 - если все.\n", r);
    int n = getInt();
    if (n == 0){
    	while (k < board->msize){
            int h = (hash1(key, board) + k * hash2(key, board)) % board->msize;
            if (board->ks[h].busy == 1 && strcmp(board->ks[h].key, key) == 0){
                board->ks[h].busy=0;
	    	free(board->ks[h].info->element);
	    	free(board->ks[h].info);
	    	free(board->ks[h].key);
            }
            k += 1;
        }
    }
    else{
	 while (k < board->msize){
            int h = (hash1(key, board) + k * hash2(key, board)) % board->msize;
            if (board->ks[h].busy == 1 && strcmp(board->ks[h].key, key) == 0 && board->ks[h].release == n){
                board->ks[h].busy=0;
                free(board->ks[h].info->element);
                free(board->ks[h].info);
                free(board->ks[h].key);
            }
	    if (board->ks[h].busy == 1 && strcmp(board->ks[h].key, key) == 0 && board->ks[h].release > n){
		board->ks[h].release -= 1;
	    }
            k += 1;
        }
    }
    return 0; //все ок
}

void Show(Table *board){
    int f = 1;
    for (int i = 0; i < board->msize; i++){
        if (board->ks[i].busy == 1){
            printf("ind: %d busy: %d key: %s release: %d element: %s\n", i, board->ks[i].busy, board->ks[i].key, board->ks[i].release, board->ks[i].info->element);
            f = 0;
        }
    }
    if (f){
        printf("Таблица пустая.\n");
    };
}

void clear(Table *board){
    for (int i = 0; i < board->msize; i++){
        if (board->ks[i].busy == 1){
            free(board->ks[i].info->element);
            free(board->ks[i].info);
            free(board->ks[i].key);
	}
    }
    free(board->ks);
}

int main() {
    Table board = {NULL, N};
    board.ks = calloc(N, sizeof(KeySpace));
    board.msize = N;
    int n = getInt();
    for (int i = 0; i < n; i++){
        printf("Введите ключ элемента:\n");
        char *key = getStr();
        printf("Введите элемент:\n");
        char *el = getStr();
        Add(&board, key, el);
        free(key);
        free(el);
    }
    Show(&board);
    int m = getInt();
    for (int i = 0; i < m; i++){
        printf("Введите ключ элемента:\n");
        char *key = getStr();
        Delete(&board, key);
	free(key);
    }
    char *key = getStr();
    char *el = getStr();
    Add(&board, key, el);
    Show(&board);
    free(key);
    free(el);
    clear(&board);
}

