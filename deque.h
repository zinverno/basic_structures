//
// Created by tamerlan on 15.06.23.
//

#ifndef BASIC_STRUCTURES_DEQUE_H
#define BASIC_STRUCTURES_DEQUE_H
#define N 1000
typedef struct Deque {
    char* vec[N];
    int n;
    int head;
    int tail;
} Deque;
int pushS_Deque(Deque* deque,char* info);
int pushE_Deque(Deque* deque,char* info);
char* popS_Deque(Deque* deque);
char* popE_Deque(Deque* deque);
void print_Deque(Deque* deque);
#endif //BASIC_STRUCTURES_DEQUE_H
