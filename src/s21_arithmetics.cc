#include "s21_matrix_oop.h"

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (std::abs(other(i, j) - (*this)(i, j)) > kEpsilon) {
        return false;
      }
    }
  }
  return true;
}
void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      (*this)(i, j) += other(i, j);
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      (*this)(i, j) -= other(i, j);
    }
  }
}

void S21Matrix::MulNumber(const double num) noexcept {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      (*this)(i, j) *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  S21Matrix tmp(rows_, other.cols_);
  if (rows_ != other.cols_) {
    throw std::out_of_range(
        "Incorrect input, first mitrix's rows should be as many as second's "
        "columns");
  }
  for (int i = 0; i < other.cols_; i++) {
    for (int j = 0; j < rows_; j++) {
      for (int k = 0; k < cols_; k++) {
        tmp(j, i) += (*this)(j, k) * (other)(k, i);
      }
    }
  }
  (*this) = tmp;
}