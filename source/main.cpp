#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

enum stack_error_t { //NOTE - при верной работе возвращаемое значение 0
    STACK_ERROR_SUCCESS = 1, //Верная работа
    STACK_ERROR_INPUT, //Ошибки связанные с переданными в функцию переменными
    STACK_ERROR_MEMORY_ALLOC, //Ошибки выделения памяти
    STACK_ERROR_SIZE_DATA,//Ошибки связанные с выходом за границу массива
    STACK_ERROR_STK_FUNC, //Ошибки связанные с некорректной работой функций
};

typedef struct {
        double *data;
        long int size;
        long int capacity;
} Stack;

// TODO
/*
    init(init_size), destroy (deinit), resize_up, push, pop, dump, verify
*/
int stack_init(Stack *, size_t init_size);
// push(stack_t *stk, double what_to_push);
int destroy(Stack *);
int resize_up(Stack *);
int resize_down(Stack *);
int push(Stack *, double elem);
int pop(Stack *, double *elem);
void dump(Stack *);


int main() {
    Stack stk = {};
    size_t init_size = 2;

    int res_init = stack_init(&stk, init_size);

    if(res_init != STACK_ERROR_SUCCESS) {
        fprintf(stderr, "err = %d\n", res_init);
        return 1;
    }

    for (int i = 0; i < 6; i++) {
        double elem = 0.0;
        scanf("%lg", &elem);
        int res_push = push(&stk, elem);
        if (res_push != STACK_ERROR_SUCCESS) {
            printf("ERROR: wrong in push\n");
            return 1;
        }
    }

    printf("\n");
    for (int n = 0; n < stk.size; n++) {
        fprintf(stderr, "data[%d] = <%lg>\n", n, stk.data[n]);
    }

    printf("\n");

    for (int i = 5; i > 0; i--) {
        double elem = 0.0;
        int res_pop = pop(&stk, &elem);
        if (res_pop != STACK_ERROR_SUCCESS) {
            printf("ERROR: wrong in push\n");
            return 1;
        }
        else
            printf("pop - <%lg>\n", elem);
    }

    dump(&stk);
    //int code = 0b00001011101011011100101011111110;

    int res_destroy = destroy(&stk);
    if (res_destroy != STACK_ERROR_SUCCESS){
        printf("ERROR: wrong destroy in main\n");
        return 1;
    }
}

int stack_init(Stack *stk, size_t init_size) {
    assert(stk);

    if (init_size == 0) {
        printf("ERROR: zero init_size, check stack_init\n");
        return STACK_ERROR_MEMORY_ALLOC;
    }

    *stk = {
                .data = (double *)calloc(init_size, sizeof(double)),
                .size = 0,
                .capacity = (long int)init_size
            };

    if (stk->data == NULL) {
        printf("ERROR: wrong first memory allocation, check #define DATA_SIZE\n");
        return STACK_ERROR_MEMORY_ALLOC;
    }

    return STACK_ERROR_SUCCESS;
}

int destroy(Stack *stk) {
    assert(stk);

    for (int i = 0; i < stk->size; i++) {
        stk->data[i] = 0.0;
    }
    free(stk->data);
    return STACK_ERROR_SUCCESS;
}

int resize_up(Stack *stk) {
    assert(stk);

    if (stk->size < stk->capacity && stk->capacity > 0)
        return STACK_ERROR_SUCCESS;

    else if(stk->size > stk->capacity || stk->capacity < 1 || stk->data == NULL){
        printf("ERROR: wrong input stk in resize_up\n");
        return STACK_ERROR_INPUT;
    }
    else{
        // fprintf(stderr, "pointer data before realloc <%p>\n", stk->data);
        stk->data = (double *) realloc(stk->data, ((size_t)stk->capacity)*2*sizeof(double)); //NOTE - stk->data - pointer, pointer = pointer

        stk->capacity = stk->capacity*2;

        if (stk->data == NULL) {
            printf("ERROR: wrong data pointer in resize_up\n");
            return STACK_ERROR_MEMORY_ALLOC;
        }
    }

    // fprintf(stderr, "pointer data after realloc <%p> capacity = <%ld> size = <%ld>\n", stk->data, stk->capacity, stk->size);
    return STACK_ERROR_SUCCESS;
}

int resize_down(Stack *stk) {
    assert(stk);

    if (stk->size > stk->capacity || stk->capacity < 1 || stk->data == NULL){
        printf("ERROR: wrong input stk in resize_up\n");
        return STACK_ERROR_INPUT;
    }
    else if (stk->size * stk->size <= stk->capacity && stk->size > 2) { //REVIEW - change 2 to 7
        stk->data = (double *)realloc(stk->data, ((size_t)stk->size + 1)*sizeof(stk->data[0]));//MENTOR - make "2" a param ??
        stk->capacity = stk->size + 1;

        if (stk->data == NULL) {
            printf("ERROR: null data pointer in resize_down\n");
            return STACK_ERROR_MEMORY_ALLOC;
        }
    }
    return STACK_ERROR_SUCCESS;
}

int push(Stack *stk, double elem) {
    assert(stk);

    if (stk->data == NULL) {
        printf("ERROR: wrong input in push\n");
        return STACK_ERROR_INPUT;
    }

    int res_resize = resize_up(stk);
    if (res_resize != STACK_ERROR_SUCCESS) {
        printf("ERROR: wrong resize_up in push\n");
        return STACK_ERROR_MEMORY_ALLOC;
    }

    if (stk->size <= stk->capacity) {
        (stk->data)[stk->size++] = elem;
    }
    else {
        printf("ERROR: wrong data size in push\n");
        return STACK_ERROR_MEMORY_ALLOC;
    }

    return STACK_ERROR_SUCCESS;
}

int pop(Stack * stk, double *elem) {
    assert(stk);
    assert(elem);

    if (stk->size > 0) {
        *elem = (stk->data)[--stk->size];
        // stk->size--;
    }
    else {
        return STACK_ERROR_SIZE_DATA;
    }

    int res_resize_down = resize_down(stk);
    if (res_resize_down != STACK_ERROR_SUCCESS) {
        printf("ERROR: wrong resize_down in pop\n");
        return STACK_ERROR_MEMORY_ALLOC;
    }

    return STACK_ERROR_SUCCESS;
}

void dump(Stack *stk) {
    printf("----------------------------------------DUMP-------------------------------------------\n");
    time_t t = time(NULL);
    printf("%s", ctime(&t));
    printf("Accessible memory: %ld\n", stk->capacity);
    printf("Memory in use: %ld\n", stk->size);
    printf("---------------------------------------------------------------------------------------\n");
}
