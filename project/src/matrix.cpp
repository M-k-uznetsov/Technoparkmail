#include "matrix.h"
#include <math.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <limits>
#include "exceptions.h"
namespace prep {
    Matrix::Matrix(size_t rows, size_t cols)
        :row(rows)
        , col(cols) {
         matrix.resize(rows, std::vector<double>(cols));
    }

    Matrix::Matrix(std::istream& is) {
        if (!is) {
            throw(InvalidMatrixStream());
        }
        is >> row >> col;
        matrix.resize(row, std::vector<double>(col));
        for (auto &row : matrix) {
            for (auto &elem : row) {
                is >> elem;
                if (!is) {
                    throw(InvalidMatrixStream());
                }
            }
        }
    }

    size_t Matrix:: getRows() const {
        return row;
    }
    size_t Matrix::getCols() const {
        return col;
    }

    double Matrix::operator()(size_t i, size_t j) const {
        if (i >= this->row || j >= this->col) {
            throw(OutOfRange(i , j , *this));
        }
        return matrix[i][j];
    }

    double& Matrix::operator()(size_t i, size_t j) {
        if (i >= this->row || j >= this->col) {
            throw(OutOfRange(i, j, *this));
        }
        return matrix[i][j];
    }

    bool Matrix::operator==(const Matrix& rhs) const {
        if (row != rhs.row || col != rhs.col) {
            return false;
        }
        for (size_t i = 0; i < row; ++i) {
            for (size_t j = 0; j < col; ++j) {
                if (std::fabs(matrix[i][j] - rhs.matrix[i][j]) >= std::numeric_limits<float>::epsilon()) {
                    return false;
                }
            }
        }
        return true;
    }

    bool Matrix::operator!=(const Matrix& rhs) const {
        return !(*this == rhs);
    }

    Matrix Matrix::operator+(const Matrix& rhs) const {
        if ((row != rhs.row) || (col != rhs.col)) {
            throw(DimensionMismatch(*this));
        }

        Matrix result_matrix(row, col);

        for (size_t i = 0; i < row; ++i) {
            for (size_t j = 0; j < col; ++j) {
                result_matrix.matrix[i][j] = matrix[i][j] + rhs.matrix[i][j];
            }
        }
        return  result_matrix;
    }

    Matrix Matrix::operator-(const Matrix& rhs) const {
        if ((row != rhs.row) || (col != rhs.col)) {
            throw(DimensionMismatch(*this));
        }

        Matrix result_matrix(row, col);

        for (size_t i = 0; i < row; ++i) {
            for (size_t j = 0; j < col; ++j) {
                result_matrix.matrix[i][j] = matrix[i][j] - rhs.matrix[i][j];
            }
        }
        return  result_matrix;
    }

    Matrix Matrix::operator*(const Matrix& rhs) const {
        if (col != rhs.row) {
            throw(DimensionMismatch(*this));
        }

        Matrix result_matrix(row, rhs.col);
        double sum = 0;
        for (size_t i = 0; i < row; ++i) {
            for (size_t j = 0; j < rhs.col; ++j) {
                for (size_t k = 0; k < rhs.row; ++k) {
                    sum += matrix[i][k] * rhs.matrix[k][j];
                }
                result_matrix.matrix[i][j] = sum;
                sum = 0;
            }
        }
        return  result_matrix;
    }

    Matrix Matrix::operator*(double val) const {
        Matrix result_matrix(row , col);
        for (size_t i = 0; i < row; ++i) {
            for (size_t j = 0; j < col; j++) {
                result_matrix.matrix[i][j] = matrix[i][j]* val;
            }
        }
        return result_matrix;
    }

    Matrix operator*(double val, const Matrix& matrix) {
        Matrix result_matrix(matrix.row , matrix.col);
        for (size_t i = 0; i < matrix.row; ++i) {
            for (size_t j = 0; j < matrix.col; j++) {
                result_matrix.matrix[i][j] = matrix.matrix[i][j]* val;
            }
        }
        return result_matrix;
    }

    std::ostream& operator<<(std::ostream& os, const prep::Matrix& matrix) {
        size_t row = matrix.row;
        size_t col = matrix.col;
        os << row << ' ' << col << '\n';
        for (size_t i = 0; i < row; ++i) {
            for (size_t j = 0; j < col; ++j) {
                os << ' '<< std::setprecision(std::numeric_limits<double>::max_digits10) << matrix.matrix[i][j] << ' ';
            }
            os << '\n';
        }
        return os;
    }

    Matrix Matrix::transp() const {
        Matrix result_matrix(col, row);
        for (size_t i = 0; i < col; ++i) {
            for (size_t j = 0; j < row; ++j) {
                result_matrix.matrix[i][j] = matrix[j][i];
            }
        }
        return result_matrix;
    }

    Matrix Matrix:: minor(size_t r, size_t c) const {
        Matrix result_matrix(row-1 , col-1);
        for (size_t i = 0 , minor_i=0; i < row-1; ++i , ++minor_i) {
            for (size_t j = 0 , minor_j=0; j < col-1; ++j , ++minor_j) {
                if (minor_i == r) {
                    ++minor_i;
                }
                if (minor_j == c) {
                    ++minor_j;
                }
                 result_matrix.matrix[i][j] = matrix[minor_i][minor_j];
            }
        }
        return result_matrix;
    }

    double Matrix::det() const {
        if (col != row) {
            throw(DimensionMismatch(*this));
        } else {
            if (col == 1) {
                return (matrix[0][0]);
            }

            if (col == 2) {
                return matrix[0][0] * matrix[1][1] -
                    matrix[0][1] * matrix[1][0];
            }
            double determinant = 0.0;
            int sign = 1;
            const Matrix minor = *this;
            for (size_t j = 0; j < col; ++j) {
                determinant += matrix[j][0] * (minor.minor(j, 0)).det() * sign;
                sign *= -1;
            }
            return determinant;
        }
    }

    Matrix Matrix::adj() const {
        Matrix transp_matr = transp();
        Matrix result_matrix(row, col);
        double sign = -1;
        for (size_t i = 0; i < row; ++i) {
            for (size_t j = 0; j < col; ++j) {
                Matrix minor = this->minor(j, i);
                result_matrix.matrix[i][j] = pow(sign, i + j) * minor.det();
            }
        }
        return result_matrix;
    }

    Matrix Matrix::inv() const {
        if (col == row && row == 1) {
            throw(SingularMatrix());
        }
        double d = det();
        if (d == 0) {
            throw(SingularMatrix() );  // what exeption is needed here?
        }
        if (row == 1) {
            Matrix result_matrix(row, col);
            result_matrix.matrix[0][0] = 1.0 / d;
            return result_matrix;
        }
        Matrix adj_matrix = adj();
        for (size_t i = 0; i < row; ++i) {
            for (size_t j = 0; j < col; ++j) {
                adj_matrix(i , j) /= d;
            }
        }
        return adj_matrix;
    }
}  // namespace prep
