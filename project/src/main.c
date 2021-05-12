#include <stdlib.h>
#include <stdio.h>

#include "utils.h"
#include "menu.h"

int main() {
    main_menu();
    int choice = 0;
    while (scanf("%d", &choice) != EOF) {
        switch (choice) {
            case MASTER_WRITE: {
                if (record_write() == EXIT_FAILURE) {
                    fprintf(stderr, "error record_write");
                    return EXIT_FAILURE;
                }
                break;
            }

            case TRANSACTION_WRITE: {
                if (transaction_write() == EXIT_FAILURE) {
                    fprintf(stderr, "error transaction_write");
                    return EXIT_FAILURE;
                }
                break;
            }

            case BLACK_RECORD: {
                if (black_record() == EXIT_FAILURE) {
                    fprintf(stderr, "error black_record");
                    return EXIT_FAILURE;
                }
                break;
            }

            default: {
                fprintf(stderr, "error menu select");
                break;
            }
        }
        clean_buffer();
        main_menu();
    }

    return EXIT_SUCCESS;
}
