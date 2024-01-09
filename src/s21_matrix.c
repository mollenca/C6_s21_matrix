#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int is_matrix_wrong = 0;
  if (rows < 1 || columns < 1 || result == NULL) {
    is_matrix_wrong = 1;
  } else {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)calloc(rows, sizeof(double *));
    for (int i = 0; i < rows; i++) {
      (result->matrix)[i] = (double *)calloc(columns, sizeof(double));
    }
  }

  return is_matrix_wrong;
}

int s21_remove_matrix(matrix_t *A) {
  for (int i = 0; i < A->rows; i++) free((A->matrix)[i]);
  free(A->matrix);
  A->rows = 0;
  A->columns = 0;

  return 0;
}

bool is_rows_and_columns_numbers_same(matrix_t *A, matrix_t *B) {
  bool result = true;
  if (A->columns != B->columns || A->rows != B->rows) {
    result = false;
  }
  return result;
}

bool is_matrix_correct(matrix_t *A) {
  bool result = 1;
  if (A == NULL || A->rows < 1 || A->columns < 1 || A->matrix == NULL)
    result = 0;
  else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (isnan(A->matrix[i][j]) || isinf(A->matrix[i][j])) {
          result = 0;
        }
      }
    }
  }
  return result;
}

bool is_matrix_columns_equal_second_rows(matrix_t *A, matrix_t *B) {
  bool result = true;
  if (A->columns != B->rows) result = false;
  return result;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int result = SUCCESS;
  if (!is_matrix_correct(A) || !is_matrix_correct(B)) {
    result = FAILURE;
  } else if (!is_rows_and_columns_numbers_same(A, B)) {
    result = FAILURE;
  } else {
    bool still_equal = 1;
    for (int i = 0; i < A->rows && still_equal; i++) {
      for (int j = 0; j < A->columns && still_equal; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-7) {
          result = FAILURE;
          still_equal = 0;
        }
      }
    }
  }

  return result;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int sum_completed = OK;
  if (!is_matrix_correct(A) || !is_matrix_correct(B) || result == NULL) {
    sum_completed = WRONG_MATRIX;
  } else if (!is_rows_and_columns_numbers_same(A, B)) {
    sum_completed = CALCULATION_ERROR;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->columns; j++)
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
  }
  return sum_completed;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int sub_completed = OK;
  if (!is_matrix_correct(A) || !is_matrix_correct(B) || result == NULL) {
    sub_completed = WRONG_MATRIX;
  } else if (!is_rows_and_columns_numbers_same(A, B)) {
    sub_completed = CALCULATION_ERROR;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->columns; j++)
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
  }
  return sub_completed;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int mul_completed = OK;
  if (!is_matrix_correct(A) || !is_matrix_correct(B)) {
    mul_completed = WRONG_MATRIX;
  } else if (!is_matrix_columns_equal_second_rows(A, B)) {
    mul_completed = CALCULATION_ERROR;
  } else {
    s21_create_matrix(A->rows, B->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        for (int k = 0; k < A->columns; k++) {
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }
  }
  return mul_completed;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int mul_completed = OK;
  if (!is_matrix_correct(A)) {
    mul_completed = WRONG_MATRIX;
  } else {
    int matrix_wrong = s21_create_matrix(A->rows, A->columns, result);
    if (matrix_wrong) {
      mul_completed = WRONG_MATRIX;
    } else {
      for (int i = 0; i < A->rows; i++)
        for (int j = 0; j < A->columns; j++)
          result->matrix[i][j] = number * A->matrix[i][j];
    }
  }
  return mul_completed;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int transpose_completed = OK;
  if (!is_matrix_correct(A)) {
    transpose_completed = WRONG_MATRIX;
  } else {
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->columns; j++)
        result->matrix[j][i] = A->matrix[i][j];
  }
  return transpose_completed;
}

bool is_matrix_square(matrix_t *A) {
  bool is_square = true;
  if (A->rows != A->columns) is_square = false;
  return is_square;
}

void copy_matrix_without_row_and_column(matrix_t A, matrix_t *result,
                                        int row_to_skip, int column_to_skip) {
  int skiped_row = 0;
  int skiped_column = 0;
  for (int row = 0; row < A.rows - 1; row++) {
    if (row == row_to_skip) {
      skiped_row = 1;
    }
    skiped_column = 0;
    for (int column = 0; column < A.columns - 1; column++) {
      if (column == column_to_skip) {
        skiped_column = 1;
      }
      result->matrix[row][column] =
          A.matrix[row + skiped_row][column + skiped_column];
    }
  }
}

double find_determinant(matrix_t A) {
  double determinant = 0;
  int sign = 1;
  if (A.rows == 1) {
    determinant = A.matrix[0][0];
  } else if (A.rows == 2) {
    determinant =
        A.matrix[0][0] * A.matrix[1][1] - A.matrix[0][1] * A.matrix[1][0];
  } else {
    for (int i = 0; i < A.columns; i++) {
      matrix_t tmp = {0};
      s21_create_matrix(A.rows - 1, A.columns - 1, &tmp);
      copy_matrix_without_row_and_column(A, &tmp, 0, i);
      determinant += sign * A.matrix[0][i] * find_determinant(tmp);
      s21_remove_matrix(&tmp);
      sign *= -1;
    }
  }
  return determinant;
}

int s21_determinant(matrix_t *A, double *result) {
  int determinant_status = OK;
  if (!is_matrix_correct(A)) {
    determinant_status = WRONG_MATRIX;
  } else if (!is_matrix_square(A)) {
    determinant_status = CALCULATION_ERROR;
  } else {
    *result = find_determinant(*A);
  }
  return determinant_status;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int complements_completed = OK;
  if (!is_matrix_correct(A)) {
    complements_completed = WRONG_MATRIX;
  } else if (!is_matrix_square(A)) {
    complements_completed = CALCULATION_ERROR;
  } else if (A->rows == 1) {
    s21_create_matrix(1, 1, result);
    result->matrix[0][0] = 1;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        matrix_t tmp = {0};
        s21_create_matrix(A->rows - 1, A->columns - 1, &tmp);
        copy_matrix_without_row_and_column(*A, &tmp, i, j);
        double determinant = 0;
        s21_determinant(&tmp, &determinant);
        result->matrix[i][j] = determinant * pow(-1, i + j);
        s21_remove_matrix(&tmp);
      }
    }
  }
  return complements_completed;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int inverse_completed = OK;

  if (!is_matrix_correct(A)) {
    inverse_completed = WRONG_MATRIX;
  } else if (!is_matrix_square(A)) {
    inverse_completed = CALCULATION_ERROR;
  } else {
    double determinant = 0;
    s21_determinant(A, &determinant);
    if (fabs(determinant) < 1e-7) {
      inverse_completed = CALCULATION_ERROR;
    } else {
      if (A->rows == 1) {
        s21_create_matrix(1, 1, result);
        result->matrix[0][0] = 1.00 / A->matrix[0][0];
      } else {
        matrix_t tmp = {0};
        matrix_t tmp1 = {0};

        s21_transpose(A, &tmp);
        s21_calc_complements(&tmp, &tmp1);
        s21_mult_number(&tmp1, 1.0 / determinant, result);

        s21_remove_matrix(&tmp);
        s21_remove_matrix(&tmp1);
      }
    }
  }
  return inverse_completed;
}
