#ifndef PROJECT_INCLUDE_MEMORY_H_
#define PROJECT_INCLUDE_MEMORY_H_

typedef struct {
    char* from;
    char* to;
    char* date;
    char* content_type;
    char* boundary;
    int cnt_boundary;
} data_t;

typedef struct {
    char** data;
    int alloc_memory;
    int current_size;
} array;

#define STARTMEMORY 100

int create_data_t(data_t* data);
void free_data_t(data_t* data);
int str_exp(array* arr);
int print_data(data_t* data);

#endif  // PROJECT_INCLUDE_MEMORY_H_
