#ifndef PROJECT_INCLUDE_BOUNDARY_H_
#define PROJECT_INCLUDE_BOUNDARY_H_

#define TRUE 2
#define FALSE 0

int del_char(char* s, int current_sumbol);
int search_in_str(char* content_type, size_t* i, char* search_word);
int get_boundary(char* content_type, char** boundary);
int check_count_part(char* boundary, int* cnt_boundary, int is_dop);

#endif  // PROJECT_INCLUDE_BOUNDARY_H_
