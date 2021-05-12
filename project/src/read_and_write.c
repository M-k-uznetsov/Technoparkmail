#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "read_and_write.h"



int write_to_file_transaction(FILE* filename, data_t* data) {
    if (filename == NULL) {
        fprintf(stderr, "no access filename");
        return EXIT_FAILURE;
    }
    if (data == NULL) {
        fprintf(stderr, "no access to write_to_file_transaction");
        return EXIT_FAILURE;
    }
    if (fprintf(filename, "%-3d%-6.2f\n",
                data->number, data->cash_payments)
        == BADINPUT) {
               return BADINPUT;
    }
    return EXIT_SUCCESS;
}


int write_to_file_record(FILE* filename, data_t* data) {
    if (filename == NULL) {
        fprintf(stderr, "no access filename");
        return EXIT_FAILURE;
    }
    if (data == NULL) {
        fprintf(stderr, "no access to write_to_file_record");
        return EXIT_FAILURE;
    }

    if (fprintf(filename, "%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n",
                data->number, data->name,
                data->surname, data->addres,
                data->tel_number, data->indebtedness,
                data->credit_limit, data->cash_payments)
        == BADINPUT) {
                return BADINPUT;
    }

    return EXIT_SUCCESS;
}


int read_from_file_transaction(FILE* filename, data_t* data) {
    if (filename == NULL) {
        fprintf(stderr, "no access filename");
        return EXIT_FAILURE;
    }
    if (data == NULL) {
        fprintf(stderr, "no access to read_from_file_transaction");
        return EXIT_FAILURE;
    }

    if (fscanf(filename, "%d%f", &data->number, &data->cash_payments)
        != TRANSACTIONEX) {
           return BADINPUT;
    }

    return EXIT_SUCCESS;
}


int read_from_file_record(FILE* filename, data_t* data) {
    if (filename == NULL) {
        fprintf(stderr, "no access filename");
        return EXIT_FAILURE;
    }
    if (data == NULL) {
        fprintf(stderr, "no access to read_from_file_record");
        return EXIT_FAILURE;
    }

    if (fscanf(filename, "%d%20s%20s%30s%15s%f%f%f",
               &data->number, data->name,
               data->surname, data->addres,
               data->tel_number, &data->indebtedness,
               &data->credit_limit, &data->cash_payments)
        != RECORDEX) {
            return BADINPUT;
    }

    return EXIT_SUCCESS;
}

