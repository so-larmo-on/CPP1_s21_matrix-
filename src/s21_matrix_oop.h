#pragma once

#ifndef S21_MATRIX_H
#define S21_MATRIX_H

#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <utility>

#define SUCCESS 1
#define FAILURE 0
#define OK 0
#define INCORRECT_MATRIX 1
#define ERROR 2
#define s21_EPS 1e-6

class S21Matrix {
 private:
  void Free() noexcept;
  const double& GetElement(int row, int col) const;

  int rows_, cols_;
  double* matrix_;

 public:
  const double kEpsilon = 1e-7;
  S21Matrix() noexcept;
  ~S21Matrix() noexcept;
  explicit S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& copy);
  S21Matrix(S21Matrix&& move) noexcept;

  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator=(S21Matrix&& other) noexcept;

  void SetRows(int rows);
  void SetCols(int cols);
  int GetRows() const noexcept;
  int GetCols() const noexcept;
  void Print();

  bool EqMatrix(const S21Matrix& other) const;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double number) noexcept;
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose() const;
  S21Matrix CalcComplements() const;
  double Determinant() const;
  S21Matrix MakeMinor(int row, int column) const;
  S21Matrix InverseMatrix() const;
  void MakeFullMatrix(double start, double step) noexcept;
  void FillMatrix(double value);

  double& operator()(int row, int col) &;
  const double& operator()(int row, int col) const&;

  bool operator==(const S21Matrix& other) const;
  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix operator*(double number) const noexcept;
  friend S21Matrix operator*(double number, const S21Matrix& matrix) noexcept;
  S21Matrix& operator*=(double number);
  S21Matrix operator*(const S21Matrix& other) const;
  S21Matrix& operator*=(const S21Matrix& other);
};

#endif  // S21_MATRIX_H