#define DEBUG_ON

#ifdef DEBUG_ON
#define DEBUG_PRINT (fmt, ...) \
    FILE *fptr = fopen("errors.txt", "w"); \
    size_t res = fwrite("DEBUG: %s:%d:%s(): " fmt "\n", \
                        __FILE__, __LINE__, __func__, __VA_ARGS__ \
                        ,1, , fptr) \
    fwrite(fptr, "Result of writing debug message: <%zu>\n", res)
#else
#define DEBUG_PRINT(fmt, ...) ((void)0)
#endif


#define SAFE_FREE(ptr, len) do { \
    for (size_t i = 0; i < len; i++) { \
        *(ptr+i) = 3735928559; \
    }
    free(p); \
    (p) = NULL; \
    } \
    while(0)

#define CHECK_ERROR(got_res, right_error, file_pointer) do {\

    if (got_res != right_error) {
        fwrite()
    }
}

if(res_init != STACK_ERROR_SUCCESS) {
        fprintf(stderr, "err = %d\n", res_init);
        return 1;
