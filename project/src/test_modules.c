#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "utils.h"
#include "read_and_write.h"

#define TESTFILE "testfile.dat"

int is_compare(data_t* got_data, data_t* expected_data) {
    if (got_data == NULL) {
        fprintf(stderr, "error got_data");
        return EXIT_FAILURE;
    }
    if (expected_data == NULL) {
        fprintf(stderr, "error expected_data");
        return EXIT_FAILURE;
    }
    if (got_data->number != expected_data->number ||
        strcmp(got_data->name, expected_data->name) != 0 ||
        strcmp(got_data->surname, expected_data->surname) != 0 ||
        strcmp(got_data->addres, expected_data->addres) != 0 ||
        strcmp(got_data->tel_number, expected_data->tel_number) != 0 ||
        got_data->indebtedness != expected_data->indebtedness ||
        got_data->credit_limit != expected_data->credit_limit ||
        got_data->cash_payments != expected_data->cash_payments) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
int is_test_write_to_file() {
    FILE* test_file = fopen(TESTFILE, "w+");
    if (test_file == NULL) {
        fprintf(stderr, "no access");
        return EXIT_FAILURE;
    }

    data_t expected_data = {1, "name", "surname", "addres", "tel_num", 500, 700, 1000 };
    if (write_to_file_record(test_file, &expected_data) != EXIT_SUCCESS) {
        fprintf(stderr, "Not acess write_to_file_record");
        fclose(test_file);
        return EXIT_FAILURE;
    }
    rewind(test_file);

    data_t got_data;
    if (read_from_file_record(test_file, &got_data) != EXIT_SUCCESS) {
        fprintf(stderr, "Not acess read_from_file_record");
        fclose(test_file);
        return EXIT_FAILURE;
    }
    fclose(test_file);

    if (is_compare(&got_data, &expected_data) != EXIT_SUCCESS) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


int main() {
    if (is_test_write_to_file() == EXIT_FAILURE) {
        printf("invalid\n");
        return EXIT_FAILURE;
    }
    printf("valid\n");

    return EXIT_SUCCESS;
}
