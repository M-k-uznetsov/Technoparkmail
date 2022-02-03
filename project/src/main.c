#include "matrix.h"

#define FILENAME "matrix.dat"


int main(void) {
    Matrix* matrix = create_matrix_from_file(FILENAME);

    size_t result_rows = 0;
    size_t result_cols = 0;
    double result_value = 0;

    get_rows(matrix, &result_rows);
    get_cols(matrix, &result_cols);
    get_elem(matrix, 1, 2, &result_value);
    mul_scalar(matrix, 3);
    transp(matrix);
    sum(matrix, transp(matrix));
    sub(matrix, transp(matrix));
    mul(matrix, transp(matrix));
    double determinant = 0;
    det(matrix, &determinant);
    adj(matrix);
    inv(matrix);
    set_elem(matrix, 2, 0, 16);
    free_matrix(matrix);
    return 0;
}
