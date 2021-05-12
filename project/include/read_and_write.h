#ifndef PROJECT_INCLUDE_READ_AND_WRITE_H_
#define PROJECT_INCLUDE_READ_AND_WRITE_H_

#define TRANSACTIONEX 2
#define RECORDEX 8
#define BADINPUT -1

int write_to_file_transaction(FILE* filename, data_t* data);
int write_to_file_record(FILE* filename, data_t* data);
int read_from_file_transaction(FILE* filename, data_t* data);
int read_from_file_record(FILE* filename, data_t* data);

#endif  // PROJECT_INCLUDE_READ_AND_WRITE_H_
