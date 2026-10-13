#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
//#include "my_debug.h"

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
