#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "read_and_write.h"
#include "menu.h"

int record_write() {
    FILE* record = fopen(FILE_RECORD, "w+");
    if (record == NULL) {
        fprintf(stderr, "Not access record");
        return EXIT_FAILURE;
    }

    data_t client;
    master_parameters();

    while (read_from_file_record(stdin, &client) == EXIT_SUCCESS) {
        clean_buffer();
        if (write_to_file_record(record, &client) != EXIT_SUCCESS) {
            fprintf(stderr, "Not acess write_to_file_record");
            fclose(record);
            return EXIT_FAILURE;
        }
        master_parameters();
    }

    clean_buffer();
    fclose(record);

    return EXIT_SUCCESS;
}


int transaction_write() {
    FILE* transaction = fopen(FILE_TRANSACTION, "r+");
    if (transaction == NULL) {
        fprintf(stderr, "Not acess transaction");
        return EXIT_FAILURE;
    }

    data_t transfer;
    transaction_parameters();

    while (read_from_file_transaction(stdin, &transfer) == EXIT_SUCCESS) {
        if (write_to_file_transaction(transaction, &transfer) != EXIT_SUCCESS) {
            fprintf(stderr, "Not acess write_to_file_transaction");
            fclose(transaction);
            return EXIT_FAILURE;
        }
        transaction_parameters();
    }

    clean_buffer();
    fclose(transaction);

    return EXIT_SUCCESS;
}


int black_record() {
    FILE* record = fopen(FILE_RECORD, "r+");
    if (record == NULL) {
        fprintf(stderr, "Not acess record");
        return EXIT_FAILURE;
    }
    FILE* transaction = fopen(FILE_TRANSACTION, "r+");
    if (transaction == NULL) {
        fclose(record);
        fprintf(stderr, "Not acess transaction");
        return EXIT_FAILURE;
    }
    FILE* blackrecord = fopen(FILE_BLACK_RECORD, "r+");
    if (blackrecord == NULL) {
        fclose(record);
        fclose(transaction);
        fprintf(stderr, "Not acess blackrecord");
        return EXIT_FAILURE;
    }

    data_t client_data, transfer;
    while (read_from_file_record(record, &client_data) == EXIT_SUCCESS) {
        while (read_from_file_transaction(transaction, &transfer) == EXIT_SUCCESS) {
            if (client_data.number == transfer.number && transfer.cash_payments != 0) {
                client_data.credit_limit += transfer.cash_payments;
            }
        }
        if (write_to_file_record(blackrecord, &client_data) != EXIT_SUCCESS) {
            fprintf(stderr, "Not acess write_to_file_blackrecord");
            fclose(record);
            fclose(transaction);
            fclose(blackrecord);
            return EXIT_FAILURE;
        }
        rewind(transaction);
    }

    fclose(record);
    fclose(transaction);
    fclose(blackrecord);

    return EXIT_SUCCESS;
}
