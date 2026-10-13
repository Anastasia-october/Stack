#include "main.h"

stack_error_t stack_init(Stack *, size_t init_size);
stack_error_t verify(Stack *, const char *);
void verifycation(Stack *, const char *);
stack_error_t destroy(Stack *);
stack_error_t resize_up(Stack *);
stack_error_t resize_down(Stack *);
stack_error_t push(Stack *, double elem);
stack_error_t pop(Stack *, double *elem);
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

    dump(&stk);
    //int code = 0b00001011101011011100101011111110;

    int res_destroy = destroy(&stk);
    if (res_destroy != STACK_ERROR_SUCCESS){
        printf("ERROR: wrong destroy in main\n");
        return 1;
    }
}

stack_error_t stack_init(Stack *stk, size_t init_size) {
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

stack_error_t verify(Stack *stk, const char *func_name) {
    assert(stk);

    if (stk->data == NULL) {
        fprintf(stderr, "ERROR: from verify: data is zero pointer in %s\n", func_name);
        return STACK_ERROR_SIZE_DATA;
    }
    if (stk->size > stk->capacity || stk->capacity <= 0) {
        fprintf(stderr, "ERROR: from verify: wrong size or capacity in %s\n", func_name);
        return STACK_ERROR_SIZE_DATA;
    }
    return STACK_ERROR_SUCCESS;
}

void verifycation(Stack *stk, const char *func_name) {
    if (verify(stk, func_name) != 1)
        exit(EXIT_FAILURE);
}

stack_error_t destroy(Stack *stk) {
    assert(stk);
    verifycation(stk, "stack_error_t destroy(Stack *stk)");

    for (int i = 0; i < stk->size; i++) {
        stk->data[i] = 0.0;
    }
    free(stk->data);
    return STACK_ERROR_SUCCESS;
}

stack_error_t resize_up(Stack *stk) {
    assert(stk);
    verifycation(stk, "stack_error_t resize_up(Stack *stk)");


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

stack_error_t resize_down(Stack *stk) {
    assert(stk);
    verifycation(stk, "stack_error_t resize_down(Stack *stk)");


    if (stk->size > stk->capacity || stk->capacity < 1 || stk->data == NULL){
        printf("ERROR: wrong input stk in resize_up\n");
        return STACK_ERROR_INPUT;
    }
    else if (stk->size * stk->size <= stk->capacity && stk->size > 2) { //REVIEW - change 2 to 7
        stk->data = (double *)realloc(stk->data, ((size_t) stk->size + 1) * sizeof(stk->data[0]));//MENTOR - make "2" a param ??
        stk->capacity = stk->size + 1;

        if (stk->data == NULL) {
            printf("ERROR: null data pointer in resize_down\n");
            return STACK_ERROR_MEMORY_ALLOC;
        }
    }
    return STACK_ERROR_SUCCESS;
}

stack_error_t push(Stack *stk, double elem) {
    assert(stk);
    verifycation(stk, "stack_error_t push(Stack *stk, double elem)");

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

stack_error_t pop(Stack *stk, double *elem) {
    assert(stk);
    assert(elem);
    verifycation(stk, "stack_error_t pop(Stack *stk, double *elem)");


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
    assert(stk);

    FILE *fp = fopen("../Stack/errors.txt", "w");
    assert(fp);

    time_t t = time(NULL);
    fprintf(fp, "%s \t Stack dump\n\n\n", ctime(&t));
    fprintf(fp, "Accessible memory: %ld\n", stk->capacity);
    fprintf(fp, "Memory in use: %ld\n\n Stack:\n", stk->size);
    for (int i = 0; i < stk->size; i++) {
        fprintf(fp, "%d \t |%lg|\n", i, stk->data[i]);
    }
    fprintf(fp, "\n\tEnd of stack\n");
    fclose(fp);
    
}
