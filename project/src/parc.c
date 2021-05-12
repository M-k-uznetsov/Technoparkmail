#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include"parc.h"
#include "memory.h"
#include "boundary.h"

int is_head_compare(FILE* email, char* current_sumbol, const char* header) {
    if (email == NULL) {
        fprintf(stderr, "error open file");
        return FALSE;
    }
    if (current_sumbol == NULL) {
        fprintf(stderr, "error current_sumbol == NULL");
        return EXIT_FAILURE;
    }
    if (header == NULL) {
        fprintf(stderr, "error first == NULL");
        return EXIT_FAILURE;
    }

    int count = 0;
    for (size_t i = 0; i < strlen(header); ++i) {
        if (*current_sumbol != header[i]) {
            fseek(email, ftell(email) - count, 0);
            return FALSE;
        }
        fscanf(email, "%c", current_sumbol);
        count += 1;
    }
    if (*current_sumbol != ' ') {
        fseek(email, ftell(email) - 1, 0);
    }
    return TRUE;
}

int parcer_body(FILE* email, char* current_sumbol, char* boundary, int* cnt_boundary, int* is_last_part) {
    if (email == NULL) {
        fprintf(stderr, "error open file");
        return EXIT_FAILURE;
    }
    if (current_sumbol == NULL) {
        fprintf(stderr, "error current_sumbol == NULL");
        return EXIT_FAILURE;
    }
    if (boundary == NULL) {
        fprintf(stderr, "error boundary == NULL");
        return EXIT_FAILURE;
    }
    if (cnt_boundary == NULL) {
        fprintf(stderr, "error cnt_boundary == NULL");
        return EXIT_FAILURE;
    }
    if (is_last_part == NULL) {
        fprintf(stderr, "error is_last_part == NULL");
        return EXIT_FAILURE;
    }
    if (*current_sumbol == boundary[0] &&
        is_head_compare(email, current_sumbol, boundary) == TRUE) {
            *cnt_boundary += 1;
            *is_last_part = FALSE;
    }
    return EXIT_SUCCESS;
}

int check_end_str(FILE* email, char* current_sumbol) {
    if (email == NULL) {
        fprintf(stderr, "error open file");
        return EXIT_FAILURE;
    }
    if (current_sumbol == NULL) {
        fprintf(stderr, "error current_sumbol == NULL");
        return EXIT_FAILURE;
    }

    int offset_count = 0;
    if (fscanf(email, "%c", current_sumbol) == EOF) {
        return EXIT_FAILURE;
    }
    offset_count +=1;
    if (*current_sumbol != '\n' && *current_sumbol != '\r') {
        return FALSE;
    }
    fscanf(email, "%c", current_sumbol);
    offset_count += 1;
    if (*current_sumbol == '\n' || *current_sumbol == '\r') {
        fscanf(email, "%c", current_sumbol);
        offset_count +=1;
    }
    if (strchr(" \t", *current_sumbol) != NULL) {
        return FALSE;
    }
    fseek(email, ftell(email) - offset_count, 0);

    return TRUE;
}

int head_check(FILE* email, char* current_sumbol, const char* header, char** key) {
    if (email == NULL) {
        fprintf(stderr, "error open file");
        return EXIT_FAILURE;
    }
    if (current_sumbol == NULL) {
        fprintf(stderr, "error current_sumbol == NULL");
        return EXIT_FAILURE;
    }
    if (header == NULL) {
        fprintf(stderr, "error first == NULL");
        return EXIT_FAILURE;
    }
    if (key == NULL) {
        fprintf(stderr, "error key == NULL");
        return EXIT_FAILURE;
    }

    if (is_head_compare(email, current_sumbol, header) != TRUE) {
        return EXIT_SUCCESS;
    }
    array arr_header;
    arr_header.data = key;
    arr_header.alloc_memory = STARTMEMORY;
    arr_header.current_size = 0;
    for (; check_end_str(email, current_sumbol) == FALSE; ++arr_header.current_size) {
        if (str_exp(&arr_header) == EXIT_FAILURE) {
            return EXIT_FAILURE;
        }
        if (*current_sumbol != '\t') {
            (*arr_header.data)[arr_header.current_size] = *current_sumbol;
        } else {
            (*arr_header.data)[arr_header.current_size] = ' ';
        }
        (*arr_header.data)[arr_header.current_size+1] = '\0';
    }

    return EXIT_SUCCESS;
}

int parcer_header(FILE* email, data_t* data, char *current_sumbol) {
    if (strlen(data->from) == 0 &&
        head_check(email, current_sumbol, FROM, &(data->from)) == EXIT_FAILURE) {
            fprintf(stderr, "error head_check_from");
            free_data_t(data);
            fclose(email);
            return EXIT_FAILURE;
    }
    if (strlen(data->to) == 0 &&
        head_check(email, current_sumbol, TO, &(data->to)) == EXIT_FAILURE) {
            fprintf(stderr, "error head_check_to");
            free_data_t(data);
            fclose(email);
            return EXIT_FAILURE;
    }
    if (strlen(data->date) == 0 &&
        head_check(email, current_sumbol, DATE, &(data->date)) == EXIT_FAILURE) {
            fprintf(stderr, "error head_check_date");
            free_data_t(data);
            fclose(email);
            return EXIT_FAILURE;
    }
    if (strlen(data->content_type) == 0) {
        if (head_check(email, current_sumbol, CONTENTTYPE, &(data->content_type)) == EXIT_FAILURE) {
            fprintf(stderr, "error head_check_content");
            free_data_t(data);
            fclose(email);
            return EXIT_FAILURE;
        }
        if (get_boundary(data->content_type, &(data->boundary)) == EXIT_FAILURE) {
            fprintf(stderr, "error head_check_get_boundary");
            free_data_t(data);
            fclose(email);
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

int check_shift_str(char current_sumbol) {
    if (current_sumbol != '\r' && current_sumbol != '\n') {
        return FALSE;
    }
    return TRUE;
}
int check_last_part(int* is_last_part, char current_sumbol) {
    if (is_last_part == NULL) {
        fprintf(stderr, "error is_last_part == NULL");
        return EXIT_FAILURE;
    }
    if (current_sumbol != '\n' &&
        current_sumbol != '\r' &&
        current_sumbol != '\t' &&
        current_sumbol != '.') {
            *is_last_part = TRUE;
    }
    return EXIT_SUCCESS;
}
