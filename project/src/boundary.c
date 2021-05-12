#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "boundary.h"
#include "memory.h"


int del_char(char* s, int current_sumbol) {
    if (s == NULL) {
       fprintf(stderr, "error s == NULL ");
        return EXIT_FAILURE;
    }
    int j = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] != current_sumbol) {
            s[j++] = s[i];
        }
    }
    s[j] = '\0';
    return EXIT_SUCCESS;
}
int search_in_str(char* content_type, size_t* i, char* search_word) {
     if (content_type == NULL) {
        fprintf(stderr, "error content_type == NULL ");
        return EXIT_FAILURE;
    }
    if (search_word == NULL) {
        fprintf(stderr, "error search_world == NULL ");
        return EXIT_FAILURE;
    }
    if (i == NULL) {
        fprintf(stderr, "error i == NULL ");
        return EXIT_FAILURE;
    }
    for (size_t j = 0; j < strlen(search_word); j++, (*i)++) {
        if (tolower(content_type[*i]) != search_word[j]) {
            return FALSE;
        }
    }

    return TRUE;
}
int extraction_boundary(char* content_type, char** boundary, size_t* i) {
    if (content_type == NULL) {
        fprintf(stderr, "error content_type == NULL ");
        return EXIT_FAILURE;
    }
    if (boundary == NULL) {
        fprintf(stderr, "error boundary == NULL ");
        return EXIT_FAILURE;
    }
    array arr_boundary;
    arr_boundary.data = boundary;
    arr_boundary.alloc_memory = STARTMEMORY;
    arr_boundary.current_size = 0;
    while (strchr(";\r\n ", content_type[*i]) == NULL) {
        if (str_exp(&arr_boundary) == EXIT_FAILURE) {
            return EXIT_FAILURE;
        }
        (*arr_boundary.data)[arr_boundary.current_size] = content_type[*i];
        (*arr_boundary.data)[arr_boundary.current_size+1] = '\0';
        arr_boundary.current_size +=1;
        ++(*i);
    }
    del_char(*boundary, '"');
    return EXIT_SUCCESS;
}
int get_boundary(char* content_type, char** boundary) {
    if (content_type == NULL) {
        fprintf(stderr, "error content_type == NULL ");
        return EXIT_FAILURE;
    }
    if (boundary == NULL) {
        fprintf(stderr, "error boundary == NULL ");
        return EXIT_FAILURE;
    }

    int is_check_multipart = FALSE;
    int is_check_boundary = FALSE;
    for (size_t i = 0; i < strlen(content_type); ++i) {
        if (is_check_multipart == FALSE &&
            tolower(content_type[i]) == 'm') {
            is_check_multipart = search_in_str(content_type, &i, "multipart");
        }
        if (is_check_multipart == TRUE &&
            is_check_boundary == FALSE &&
            tolower(content_type[i]) == 'b' &&
            (content_type[i-1] == ' ' ||content_type[i-1] == ';')) {
            is_check_boundary = search_in_str(content_type, &i, "boundary=");
            ++i;
        }

        if (is_check_boundary == TRUE && strlen(*boundary) == 0) {
            if (extraction_boundary(content_type, boundary, &i) == EXIT_FAILURE) {
                return EXIT_FAILURE;
            }
            return EXIT_SUCCESS;
        }
    }
    return EXIT_SUCCESS;
}

int check_count_part(char* boundary, int* cnt_boundary, int is_last_part) {
    if (boundary == NULL) {
        fprintf(stderr, "error boundary == NULL ");
        return EXIT_FAILURE;
    }
    if (cnt_boundary == NULL) {
        fprintf(stderr, "error cnt_boundary == NULL ");
        return EXIT_FAILURE;
    }

    if (is_last_part == TRUE) {
        *cnt_boundary += 1;
    }
    if (strlen(boundary) == 0) {
        *cnt_boundary = 1;
    }

    return EXIT_SUCCESS;
}
