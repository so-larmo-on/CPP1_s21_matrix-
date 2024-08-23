#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() noexcept : rows_(0), cols_(0), matrix_(nullptr) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows_ < 0 || cols_ < 0) {
    throw std::length_error("Matrix size must be greater or equal 0");
  } else {
    matrix_ = new double[rows_ * cols_]{};
  }
}

S21Matrix::S21Matrix(const S21Matrix &copy)
    : rows_(copy.rows_), cols_(copy.cols_), matrix_(new double[rows_ * cols_]) {
  std::copy(copy.matrix_, copy.matrix_ + rows_ * cols_, matrix_);
}

S21Matrix::S21Matrix(S21Matrix &&other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

S21Matrix::~S21Matrix() noexcept { Free(); }

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  S21Matrix copy(other);
  *this = std::move(copy);
  return *this;
}

S21Matrix &S21Matrix::operator=(S21Matrix &&other) noexcept {
  if (this != &other) {
    Free();

    std::swap(rows_, other.rows_);
    std::swap(cols_, other.cols_);
    std::swap(matrix_, other.matrix_);
  }

  return *this;
}

double &S21Matrix::operator()(int row, int col) & {
  return const_cast<double &>(GetElement(row, col));
}

const double &S21Matrix::operator()(int row, int col) const & {
  const double &el = GetElement(row, col);
  return el;
}

bool S21Matrix::operator==(const S21Matrix &other) const {
  return EqMatrix(other);
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) const {
  S21Matrix tmp{*this};
  tmp.SumMatrix(other);
  return tmp;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) const {
  S21Matrix tmp{*this};
  tmp.SubMatrix(other);
  return tmp;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*(double number) const noexcept {
  S21Matrix tmp(*this);
  tmp.MulNumber(number);
  return tmp;
}

S21Matrix operator*(double number, const S21Matrix &matrix) noexcept {
  S21Matrix tmp = matrix * number;
  return tmp;
}

S21Matrix &S21Matrix::operator*=(double number) {
  MulNumber(number);
  return *this;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) const {
  S21Matrix tmp(*this);
  tmp.MulMatrix(other);
  return tmp;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);
  return *this;
}

void S21Matrix::Free() noexcept {
  delete[] matrix_;
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

const double &S21Matrix::GetElement(int row, int col) const {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0) {
    throw std::out_of_range("Incorrect input for (), index is out of range.");
  }
  return matrix_[row * cols_ + col];
}

void S21Matrix::SetRows(int new_rows) {
  if (new_rows < 0) {
    throw std::length_error("matrix rows count must be non-negative");
  }

  if (new_rows != rows_) {
    S21Matrix tmp{new_rows, cols_};
    int min = rows_ < new_rows ? rows_ : new_rows;
    for (int i = 0; i < min; ++i) {
      for (int j = 0; j < cols_; ++j) {
        tmp(i, j) = (*this)(i, j);
      }
    }
    *this = std::move(tmp);
  }
}

void S21Matrix::SetCols(int new_cols) {
  if (new_cols < 0) {
    throw std::length_error("matrix rows count must be non-negative");
  }

  if (new_cols != cols_) {
    S21Matrix tmp{rows_, new_cols};
    int min = cols_ < new_cols ? cols_ : new_cols;
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < min; ++j) {
        tmp(i, j) = (*this)(i, j);
      }
    }

    *this = std::move(tmp);
  }
}

int S21Matrix::GetRows() const noexcept { return rows_; }

int S21Matrix::GetCols() const noexcept { return cols_; }
