//
// Created by tamerlan on 15.06.23.
//

#include <stdio.h>
#include <string.h>
#include "deque.h"
#define vec deque->vec
#define n deque->n
#define head deque->head
#define tail deque->tail
int pushS_Deque(Deque* deque,char* info){
    n++;
    if(n>N){
        perror("overflow");
        return 1;
    }
    if(--(head) < 0)
        head = N - 1;
    vec[head]=info;
    return 0;
}
int pushE_Deque(Deque* deque,char* info){
    n++;
    if(n>N){
        perror("overflow");
        return 1;
    }
    vec[tail]=info;
    tail=(tail+1)%N;
    return 0;
}
char* popS_Deque(Deque* deque){
    if(n==0){
        perror("emty deque");
        return NULL;
    }
    n--;
    char* str=strdup(vec[head]);
    head=(head+1)%N;
    return str;
}
char* popE_Deque(Deque* deque){
    if(n==0){
        perror("emty deque");
        return NULL;
    }
    n--;
    tail=(tail-1)%N;
    char* str=strdup(vec[tail]);
    vec[tail]=NULL;
    return str;
}
void print_Deque(Deque* deque){
    int i=0;
    while (i!=N){
        if(vec[i]) {
            printf("%s\n", vec[i]);
        }
        i++;
    }
}