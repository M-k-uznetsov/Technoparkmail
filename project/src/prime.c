#include "prime.h"
#include "math.h"
#include <stdio.h>

int is_prime(int value) {
    if (value <= 1) {
        return 0;
    }

    for (int i = 2; i * i < value; i++) {
        if (value % i == 0) {
            return 0;
        }
    }

    return 1;
}
