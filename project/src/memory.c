#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "memory.h"
#include "parc.h"
void free_data_t(data_t* data) {
    if (data->from) {
        free(data->from);
    }

    if (data->to) {
        free(data->to);
    }

    if (data->date) {
        free(data->date);
    }

    if (data->content_type) {
        free(data->content_type);
    }

    if (data->boundary) {
        free(data->boundary);
    }
}

int create_data_t(data_t* data) {
    if (data == NULL) {
        fprintf(stderr, "error data == NULL");
        return EXIT_FAILURE;
    }
    int len_data = STARTMEMORY;
    data->from = calloc(len_data+1, sizeof(char));
    if (data->from == NULL) {
        fprintf(stderr, "error create from ");
        return EXIT_FAILURE;
    }
    data->to = calloc(len_data+1, sizeof(char));
    if (data->to == NULL) {
        fprintf(stderr, "error create to ");
        free_data_t(data);
        return EXIT_FAILURE;
    }
    data->date = calloc(len_data+1, sizeof(char));
    if (data->date == NULL) {
        fprintf(stderr, "error create date ");
        free_data_t(data);
        return EXIT_FAILURE;
    }
    data->content_type = calloc(len_data+1, sizeof(char));
    if (data->content_type == NULL) {
        fprintf(stderr, "error create content_type ");
        free_data_t(data);
        return EXIT_FAILURE;
    }
    data->boundary = calloc(len_data+1, sizeof(char));
    if (data->boundary == NULL) {
        fprintf(stderr, "error create boundary ");
        free_data_t(data);
        return EXIT_FAILURE;
    }
    data->cnt_boundary = -1;
    return EXIT_SUCCESS;
}

int str_exp(array* arr) {
    if (arr == NULL) {
        fprintf(stderr, "error arr == NULL");
        return EXIT_FAILURE;
    }
    if (arr->current_size != arr->alloc_memory) {
        return EXIT_SUCCESS;
    }
    arr->alloc_memory *= 2;
    *(arr->data) = realloc(*(arr->data), arr->alloc_memory+1);
    if (*(arr->data) == NULL) {
        fprintf(stderr, "error realloc process");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int print_data(data_t* data) {
     if (data == NULL) {
        fprintf(stderr, "error data == NULL");
        return EXIT_FAILURE;
     }

    printf("%s|%s|%s|%d", data->from, data->to, data->date, data->cnt_boundary);

    return EXIT_SUCCESS;
}
