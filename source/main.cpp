#include <stdio.h>
#include <assert.h>

#define DATA_SIZE 5

int push(struct Stack *, double elem);
int pop(struct Stack *, double *elem);

struct Stack {
        double data[DATA_SIZE];
        size_t size;
        size_t capacity;
};

int main() {
    struct Stack stk1 = {{}, 0, DATA_SIZE};
    int res1 = push(&stk1, 1.3);
    assert (res1);
    int res2 = push(&stk1, 2.3);
    assert (res2);

    double smth = 8.9;
    int res3 = pop(&stk1, &smth);
    printf("res3 - %d, popped - %lg\n", res3, smth);
}

int push(struct Stack *stk1, double elem) {
    assert(stk1);

    if (stk1->size < stk1->capacity) {
        (stk1->data)[stk1->size] = elem;
        stk1->size++;
    }
    else {
        return -1;
    }
    return 1;
}

int pop(struct Stack * stk1, double *elem) {
    assert(stk1);

    if (stk1->size > 0) {
        *elem = (stk1->data)[--stk1->size];
        stk1->size;
    }
    else {
        return -1;
    }
    return 1;
}
