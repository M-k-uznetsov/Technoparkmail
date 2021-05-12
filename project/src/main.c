#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "boundary.h"
#include "parc.h"
#include "memory.h"

int main(int argc, const char** argv) {
    if (argc != 2) {
        fprintf(stderr, "no argv");
        return EXIT_FAILURE;
    }
    FILE* email = fopen(argv[1], "r");
    if (email == NULL) {
        fprintf(stderr, "error open source file ");
        return EXIT_FAILURE;
    }
    data_t data;
    create_data_t(&data);

    int is_shift_str = TRUE;
    int is_last_part = FALSE;
    char current_sumbol;

    while (fscanf(email, "%c", &current_sumbol) != EOF) {
        if (is_shift_str == TRUE) {
            if (check_last_part(&is_last_part, current_sumbol) == EXIT_FAILURE) {
                fprintf(stderr, "error check_last_part");
                free_data_t(&data);
                fclose(email);
                return EXIT_FAILURE;
            }
            if (parcer_header(email, &data, &current_sumbol) == EXIT_FAILURE) {
                fprintf(stderr, "error check_error_parcer_header");
                free_data_t(&data);
                fclose(email);
                return EXIT_FAILURE;
            }
        }

        is_shift_str = check_shift_str(current_sumbol);

        if (parcer_body(email, &current_sumbol, data.boundary,
            &data.cnt_boundary, &is_last_part) == EXIT_FAILURE) {
            fprintf(stderr, "error check_error_parcer_body");
            free_data_t(&data);
            fclose(email);
            return EXIT_FAILURE;
        }
    }

    if (check_count_part(data.boundary, &data.cnt_boundary, is_last_part) == EXIT_FAILURE) {
        fprintf(stderr, "error check_boundary");
        free_data_t(&data);
        fclose(email);
        return EXIT_FAILURE;
    }

    if (print_data(&data) == EXIT_FAILURE) {
        fprintf(stderr, "error print_data");
        free_data_t(&data);
        fclose(email);
        return EXIT_FAILURE;
    }

    free_data_t(&data);
    fclose(email);
    return EXIT_SUCCESS;
}
