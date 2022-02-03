#include "utils.h"
#include <stddef.h>

size_t custom_strlen(const char* str) {
    size_t l = 0;
    while (*str != '\0') {
        l++;
        str++;
    }
    return l;
}


int custom_pow(int base, int power) {
    int x = 1;
    for (int i = 0 ; i < power ; i++) {
    	x *= base;
    }
    return x;
}

