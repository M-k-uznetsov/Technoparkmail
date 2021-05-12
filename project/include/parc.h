#ifndef PROJECT_INCLUDE_PARC_H_
#define PROJECT_INCLUDE_PARC_H_

#include "memory.h"

#define TRUE 2
#define FALSE 0

#define FROM "From:"
#define TO "To:"
#define DATE "Date:"
#define CONTENTTYPE "Content-Type:"


int is_head_compare(FILE* email, char* current_sumbol, const char* header);
int parcer_body(FILE* email, char* current_sumbol, char* boundary, int* cnt_boundary, int* is_last_part);
int check_end_str(FILE* email, char* current_sumbol);
int head_check(FILE* email, char* current_sumbol, const char* header, char** key);
int parcer_header(FILE* email, data_t* data, char *current_sumbol);
int check_shift_str(char current_sumbol);
int check_last_part(int* is_last_part, char current_sumbol);

#endif  // PROJECT_INCLUDE_PARC_H_
