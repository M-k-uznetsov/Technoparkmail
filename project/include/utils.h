#ifndef PROJECT_INCLUDE_UTILS_H_
#define PROJECT_INCLUDE_UTILS_H_
#define FILE_RECORD "record.dat"
#define FILE_TRANSACTION "transaction.dat"
#define FILE_BLACK_RECORD "blackrecord.dat"

enum Switch {
    MASTER_WRITE = 1,
    TRANSACTION_WRITE,
    BLACK_RECORD
};

typedef struct {
    int number;
    char name[20];
    char surname[20];
    char addres[30];
    char tel_number[15];
    float indebtedness;
    float credit_limit;
    float cash_payments;
} data_t;

int black_record();
int record_write();
int transaction_write();

#endif  // PROJECT_INCLUDE_UTILS_H_
