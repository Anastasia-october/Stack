#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

enum stack_error_t { //NOTE - при верной работе возвращаемое значение 0
    STACK_ERROR_SUCCESS = 1,
    STACK_ERROR_INPUT,
    STACK_ERROR_MEMORY_ALLOC, //Ошибки выделения памяти
    STACK_ERROR_SIZE_DATA,//Ошибки связанные с выходом за границу массива
    STACK_ERROR_STK_FUNC, //Ошибки связанные с некорректной работой функций
};

typedef struct Stack {
        double *data;
        long int size;
        long int capacity;
} Stack;

// TODO
/*
    init(init_size), destroy (deinit), resize, push, pop, dump, verify
*/
int stack_init(Stack *, size_t init_size);
int resize(Stack *);
int push(Stack *);
int pop(Stack *, double *elem);
void dump(Stack *);


int main() {
    Stack stk;
    size_t init_size = 2;

    int res_init = stack_init(&stk, init_size);
    if(res_init > 0)
        return 0;

    for (int i = 0; i < 7; i++) {
        push(&stk);
    }

    for (int n = 0; n < stk.size; n++) {
        printf("data[%d] = <%lg>\n", n, stk.data[n]);
    }

    free(stk.data);
}

int stack_init(Stack *stk, size_t init_size) {
    assert(stk);

    if (init_size == 0) {
        printf("ERROR: zero init_size, check stack_init\n");
        return STACK_ERROR_MEMORY_ALLOC;
    }

    *stk = {(double *)calloc(init_size, sizeof(double)), 0, (long int)init_size};

    if (stk->data == NULL) {
        printf("ERROR: wrong first memory allocation, check #define DATA_SIZE\n");
        return STACK_ERROR_MEMORY_ALLOC;
    }

    return STACK_ERROR_SUCCESS;
}

int push(Stack *stk) {
    assert(stk);

    double elem = 0.0;
    if (scanf("%lg", &elem) != 1) {
        printf("ERROR: wrong input in push\n");
        return STACK_ERROR_INPUT;
    }

    int res_resize = resize(stk);
    if (res_resize > 0) {
        printf("ERROR: wrong resize in push\n");
        return STACK_ERROR_MEMORY_ALLOC;
    }

    if (stk->size < stk->capacity) {
        (stk->data)[stk->size] = elem;
        stk->size++;
    }
    else {
        printf("ERROR: wrong data size in push\n");
        return STACK_ERROR_MEMORY_ALLOC;
    }
    return STACK_ERROR_SUCCESS;
}

int pop(struct Stack * stk, double *elem) {
    assert(stk);
    assert(elem);

    if (stk->size > 0) {
        *elem = (stk->data)[stk->size--];
    }
    else {
        return STACK_ERROR_SIZE_DATA;
    }
    return STACK_ERROR_SUCCESS;
}

void dump(Stack *stk) {
    time_t t = time(NULL);
    printf("%s\n", ctime(&t));
    printf("Accessible memory: %ld\n", stk->capacity);
    printf("Memory in use: %ld\n", stk->size);
}

int resize(Stack *stk) {
    assert(stk);

    if (stk->size < stk->capacity && stk->capacity > 0)
        return STACK_ERROR_SUCCESS;

    else if(stk->size > stk->capacity || stk->capacity < 1 || stk->data == NULL){
        printf("ERROR: wrong input stk in resize\n");
        return STACK_ERROR_INPUT;
    }
    else{
        stk->data = (double *)realloc(stk->data, 2*(size_t)stk->capacity);
        if (stk->data == NULL)
            return STACK_ERROR_MEMORY_ALLOC;
    }
    return STACK_ERROR_SUCCESS;
}
