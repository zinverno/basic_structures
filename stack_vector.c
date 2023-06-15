#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Data {
    char *data;
} Data;
typedef struct Stack{
    int max_len;
    int len;
    Data *arr;
} Stack;
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
int push(Stack *stack, char *el){
    if (stack->max_len <= stack->len){
        printf("Переполнение\n");
        /*printf("1 - Увеличить размер в 2 раза?\n1-Да\n2-Нет");
        int n;
        scanf("%d", &n);
        if (n == 1){
            stack->max_len *= 2;
            stack->arr = realloc(sizeof(Data) * stack->max_len);
        }
        else{
            return;
        }*/
        return 0;
    }
    stack->arr[stack->len].data = strdup(el);
    stack->len += 1;
    return 1;
}
char *pop(Stack *stack){
    if (stack->len == 0){
        printf("Стек пуст\n");
        return NULL;
    }
    else{
        char *el = strdup(stack->arr[stack->len-1].data);
	stack->len -=1;
        return el;
    }
}
void show(Stack *stack){
    for (int i = 0; i < stack->len; i++){
        printf("%s ", stack->arr[i].data);
    }
}
void clear(Stack *stack){
    for (int i = 0; i < stack->max_len; i++){
       	free(stack->arr[i].data);
    }
    free(stack->arr);
    free(stack);
}
int main() {
    Stack *stack = malloc(sizeof(Stack));
    stack->len = 0;
    int max_len;
    scanf("%d", &max_len);
    stack->max_len = max_len;
    stack->arr = (Data *) calloc(max_len, sizeof(Data));
    int n;
    scanf("%d ", &n);
    for (int i = 0; i < n; i++){
        char *el = getStr();
        push(stack, el);
        free(el);
    }
    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; i++){
        char *el = pop(stack);
        if (el){
            printf("%s ", el);
        }
        free(el);
    }
    printf("\n");
    show(stack);
    clear(stack);
    return 0;
}

