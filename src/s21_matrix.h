#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0

#define OK 0
#define WRONG_MATRIX 1
#define CALCULATION_ERROR 2

#define FAIL 1

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int s21_create_matrix(int rows, int columns, matrix_t *result);
int s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

// help functions
bool is_rows_and_columns_numbers_same(matrix_t *A, matrix_t *B);
bool is_matrix_correct(matrix_t *A);
bool is_matrix_columns_equal_second_rows(matrix_t *A, matrix_t *B);
bool is_matrix_square(matrix_t *A);
void copy_matrix_without_row_and_column(matrix_t A, matrix_t *result,
                                        int row_to_skip, int column_to_skip);
