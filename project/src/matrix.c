#include <malloc.h>

#include "matrix.h"

Matrix* create_matrix_from_file(const char* path_file) {
    if (!path_file) {
        return NULL;
    }

    FILE* file_matrix = fopen(path_file, "r");
    if (!file_matrix) {
        return NULL;
    }
    size_t rows = 0;
    size_t cols = 0;

    if (fscanf(file_matrix, "%zu%zu", &rows, &cols) != 2) {
        fclose(file_matrix);
        return NULL;
    }

    Matrix* matrix = create_matrix(rows, cols);
    if (!matrix) {
        fclose(file_matrix);
        return NULL;
    }
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            if (fscanf(file_matrix, "%lf", &matrix->data[i][j]) != 1) {
                fclose(file_matrix);
                free_matrix(matrix);
                return NULL;
            }
        }
    }

    fclose(file_matrix);

    return matrix;
}

Matrix* create_matrix(size_t rows, size_t cols) {
    Matrix* matrix = malloc(sizeof(Matrix));
    if (!matrix) {
        return NULL;
    }
    matrix->row = rows;
    matrix->col = cols;
    matrix->data = malloc(matrix->row * matrix->col * sizeof(double*));
    if (!matrix->data) {
        free_matrix(matrix);
        return NULL;
    }
    for (size_t i = 0; i < rows; ++i) {
        matrix->data[i] = calloc(cols, sizeof(double));
        if (!matrix->data[i]) {
            free_matrix(matrix);
            return NULL;
        }
    }
    return matrix;
}

int free_matrix(Matrix* matrix) {
    if (!matrix) {
        return -1;
    }
    for (size_t i = 0; i < matrix->row; ++i) {
        free(matrix->data[i]);
    }
    free(matrix->data);
    free(matrix);
    return 0;
}

// Basic operations
int get_rows(const Matrix* matrix, size_t* rows) {
    if (!matrix) {
        return -1;
    }
    *rows = matrix->row;

    return 0;
}

int get_cols(const Matrix* matrix, size_t* cols) {
    if (!matrix) {
        return -1;
    }
    *cols = matrix->col;

    return 0;
}

int get_elem(const Matrix* matrix, size_t row, size_t col, double* val) {
    if ((!matrix) || (!val)) {
        return -1;
    }
    *val = matrix->data[row][col];

    return 0;
}

int set_elem(Matrix* matrix, size_t row, size_t col, double val) {
    if (!matrix) {
        return -1;
    }
    matrix->data[row][col] = val;

    return 0;
}

//  Math operations
Matrix* mul_scalar(const Matrix* matrix, double val) {
    if (!matrix) {
        return NULL;
    }
    Matrix* result_matrix = create_matrix(matrix->row, matrix->col);
    if (!result_matrix) {
        return NULL;
    }
    for (size_t i = 0; i < matrix->row; ++i) {
        for (size_t j = 0; j < matrix->col; ++j) {
            result_matrix->data[i][j] = matrix->data[i][j] * val;
        }
    }

    return result_matrix;
}

Matrix* transp(const Matrix* matrix) {
    if (!matrix) {
        return NULL;
    }
    Matrix* result_matrix = create_matrix(matrix->col, matrix->row);
    if (!result_matrix) {
        return NULL;
    }

    for (size_t i = 0; i < matrix->col; ++i) {
        for (size_t j = 0; j < matrix->row; ++j) {
            result_matrix->data[i][j] = matrix->data[j][i];
        }
    }

    return result_matrix;
}

Matrix* sum(const Matrix* l, const Matrix* r) {
    if ((l->row != r->row) || (l->col != r->col)) {
        return NULL;
    }

    Matrix* result_matrix = create_matrix(l->row, r->col);
    if (!result_matrix) {
        return NULL;
    }
    for (size_t i = 0; i < l->row; ++i) {
        for (size_t j = 0; j < r->col; ++j) {
            result_matrix->data[i][j] = l->data[i][j] + r->data[i][j];
        }
    }

    return result_matrix;
}

Matrix* sub(const Matrix* l, const Matrix* r) {
    if ((l->row != r->row) || (l->col != r->col)) {
        return NULL;
    }
    Matrix* result_matrix = create_matrix(l->row, r->col);
    if (!result_matrix) {
        return NULL;
    }

    for (size_t i = 0; i < l->row; ++i) {
        for (size_t j = 0; j < r->col; ++j) {
            result_matrix->data[i][j] = l->data[i][j] - r->data[i][j];
        }
    }

    return result_matrix;
}

Matrix* mul(const Matrix* l, const Matrix* r) {
    if (l->col != r->row) {
        return NULL;
    }

    Matrix* result_matrix = create_matrix(l->row, r->col);
    if (!result_matrix) {
        return NULL;
    }
    double s = 0;
    for (size_t i = 0; i < l->row; ++i) {
        for (size_t j = 0; j < r->col; ++j) {
            for (size_t k = 0; k < r->row; ++k) {
                s += l->data[i][k] * r->data[k][j];
            }
            result_matrix->data[i][j] = s;
            s = 0;
        }
    }
    return result_matrix;
}


// Extra operations
int det(const Matrix* matrix, double* val) {
    if (!matrix || !val) {
        return -1;
    }

    return 0;
}
Matrix* adj(const Matrix* matrix) {
    if (!matrix) {
        return NULL;
    }

    return NULL;
}
Matrix* inv(const Matrix* matrix) {
    if (!matrix) {
        return NULL;
    }

    return NULL;
}
