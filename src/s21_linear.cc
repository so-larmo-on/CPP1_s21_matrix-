#include "s21_matrix_oop.h"

//меняем столб со стр
S21Matrix S21Matrix::Transpose() const {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < cols_; i++) {
    for (int j = 0; j < rows_; j++) {
      result(i, j) = (*this)(j, i);
    }
  }
  return result;
}
//матрица определителей
S21Matrix S21Matrix::CalcComplements() const {
  S21Matrix result(rows_, cols_);
  if (rows_ != cols_) {
    throw std::out_of_range("Incorrect input, matrix must be squared");
  } else if (rows_ == 1) {
    result(0, 0) = 1;
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        S21Matrix minor(rows_ - 1, cols_ - 1);
        minor = MakeMinor(i, j);
        double det = 0;
        det = minor.Determinant();
        result(i, j) = det * pow(-1, i + j);
      }
    }
  }
  return result;
}

double S21Matrix::Determinant() const {
  double det = 0;
  if (rows_ != cols_) {
    throw std::out_of_range("Incorrect input, rows must be equal to cols");
  }
  if (rows_ == 1) {
    det = (*this)(0, 0);
  } else if (rows_ == 2) {
    det = (*this)(0, 0) * (*this)(1, 1) - (*this)(0, 1) * (*this)(1, 0);
  } else {
    int sign = 1;
    for (auto i = 0; i < cols_; i++) {
      double minor_determinant = 0;
      S21Matrix minor(rows_ - 1, cols_ - 1);
      minor = (this)->MakeMinor(0, i);
      minor_determinant = minor.Determinant();
      det += sign * (*this)(0, i) * minor_determinant;
      sign *= -1;
    }
  }
  return det;
}

//минор 3 нп 3
S21Matrix S21Matrix::MakeMinor(int row, int column) const {
  S21Matrix tmp(rows_ - 1, cols_ - 1);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (i != row && j != column) {
        tmp(i - (i > row), j - (j > column)) = (*this)(i, j);
      }
    }
  }
  return tmp;
}
//обратная матрица
S21Matrix S21Matrix::InverseMatrix() const {
  double det = 0;
  S21Matrix result(rows_, cols_);
  if (rows_ != cols_) {
    throw std::out_of_range(
        "Incorrect input, first mitrix's rows should be as many as second's "
        "columns");
  }
  if (rows_ == 1) {
    result(0, 0) = (*this)(0, 0) == 0 ? 1 : 1.0 / (*this)(0, 0);
    return result;
  }
  S21Matrix calc_complements;
  det = (*this).Determinant();
  if ((fabs(det - 0) <= 1e-06)) { //gпроверка на детерменант = 0
    throw std::out_of_range(
        "Incorrect input, mitrix's determinant must be different from zero");
  }
  if (rows_ > 1) {
    calc_complements = (*this).CalcComplements();
    result = calc_complements.Transpose();
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        result(i, j) /= det;
      }
    }
  }
  return result;
}