#include "test.h"

TEST(LinearOperations, Transpose) {
  auto test1 = S21Matrix(3, 3);
  for (int i = 0; i < test1.GetRows(); i++) {
    for (int j = 0; j < test1.GetCols(); j++) {
      test1(i, j) = test1.GetRows() * i + j + 1;
    }
  }
  test1 = test1.Transpose();
  auto test2 = S21Matrix(3, 3);
  test2(0, 0) = 1;
  test2(0, 1) = 4;
  test2(0, 2) = 7;
  test2(1, 0) = 2;
  test2(1, 1) = 5;
  test2(1, 2) = 8;
  test2(2, 0) = 3;
  test2(2, 1) = 6;
  test2(2, 2) = 9;
  EXPECT_EQ(test1, test2);
}

TEST(LinearOperations, CalcComplements) {
  auto test1 = S21Matrix(3, 3);
  test1(0, 0) = 1;
  test1(0, 1) = 2;
  test1(0, 2) = 3;
  test1(1, 0) = 0;
  test1(1, 1) = 4;
  test1(1, 2) = 2;
  test1(2, 0) = 5;
  test1(2, 1) = 2;
  test1(2, 2) = 1;
  test1 = test1.CalcComplements();
  auto test2 = S21Matrix(3, 3);
  test2(0, 0) = 0;
  test2(0, 1) = 10;
  test2(0, 2) = -20;
  test2(1, 0) = 4;
  test2(1, 1) = -14;
  test2(1, 2) = 8;
  test2(2, 0) = -8;
  test2(2, 1) = -2;
  test2(2, 2) = 4;
  EXPECT_EQ(test1, test2);
}

TEST(LinearOperations, Determinant) {
  auto test1 = S21Matrix(3, 3);
  test1(0, 0) = 1;
  test1(0, 1) = 2;
  test1(0, 2) = 3;
  test1(1, 0) = 0;
  test1(1, 1) = 4;
  test1(1, 2) = 2;
  test1(2, 0) = 5;
  test1(2, 1) = 2;
  test1(2, 2) = 1;
  EXPECT_DOUBLE_EQ(test1.Determinant(), -40);

  S21Matrix m(1, 1);
  double det = m.Determinant();
  EXPECT_EQ(det, 0.0);
}

TEST(LinearOperations, InverseMatrix) {
  auto test1 = S21Matrix(3, 3);
  test1(0, 0) = 2;
  test1(0, 1) = 5;
  test1(0, 2) = 7;
  test1(1, 0) = 6;
  test1(1, 1) = 3;
  test1(1, 2) = 4;
  test1(2, 0) = 5;
  test1(2, 1) = -2;
  test1(2, 2) = -3;
  test1 = test1.InverseMatrix();
  auto test2 = S21Matrix(3, 3);
  test2(0, 0) = 1;
  test2(0, 1) = -1;
  test2(0, 2) = 1;
  test2(1, 0) = -38;
  test2(1, 1) = 41;
  test2(1, 2) = -34;
  test2(2, 0) = 27;
  test2(2, 1) = -29;
  test2(2, 2) = 24;
  EXPECT_EQ(test1, test2);

  S21Matrix m(1, 1);
  S21Matrix r = m.InverseMatrix();
  EXPECT_EQ(r(0, 0), 1);
}
TEST(TestCalcComplements, TestCalcComplementsException1) {
  S21Matrix test_matrix(2, 3);
  S21Matrix matrix_before = test_matrix;

  EXPECT_ANY_THROW(test_matrix.CalcComplements());
  EXPECT_TRUE(test_matrix == matrix_before);
  S21Matrix row1(1, 1);
  S21Matrix res = row1.CalcComplements();
}

TEST(TestCalcComplements, TestCalcComplementsException2) {
  S21Matrix test_matrix(3, 2);

  EXPECT_EQ(test_matrix.GetRows(), 3);
  EXPECT_EQ(test_matrix.GetCols(), 2);

  S21Matrix matrix_before = test_matrix;

  EXPECT_ANY_THROW(test_matrix.CalcComplements());
  EXPECT_TRUE(test_matrix == matrix_before);
}

TEST(TestCalcComplements, TestCalcComplementsException3) {
  S21Matrix test_matrix(1, 5);

  EXPECT_EQ(test_matrix.GetRows(), 1);
  EXPECT_EQ(test_matrix.GetCols(), 5);

  S21Matrix matrix_before = test_matrix;

  EXPECT_ANY_THROW(test_matrix.CalcComplements());
  EXPECT_TRUE(test_matrix == matrix_before);
}

TEST(TestCalcComplements, TestCalcComplementsException4) {
  S21Matrix test_matrix(5, 1);

  EXPECT_EQ(test_matrix.GetRows(), 5);
  EXPECT_EQ(test_matrix.GetCols(), 1);

  S21Matrix matrix_before = test_matrix;

  EXPECT_ANY_THROW(test_matrix.CalcComplements());
  EXPECT_TRUE(test_matrix == matrix_before);
}

TEST(TestCalcComplements, TestCalcComplementsException5) {
  S21Matrix test_matrix(29, 30);

  EXPECT_EQ(test_matrix.GetRows(), 29);
  EXPECT_EQ(test_matrix.GetCols(), 30);

  test_matrix.FillMatrix(1.99);

  S21Matrix matrix_before = test_matrix;

  EXPECT_ANY_THROW(test_matrix.CalcComplements());
  EXPECT_TRUE(test_matrix == matrix_before);
}

TEST(TestCalcComplements, TestCalcComplementsOne1) {
  S21Matrix test_matrix(1, 1);

  EXPECT_EQ(test_matrix.GetRows(), 1);
  EXPECT_EQ(test_matrix.GetCols(), 1);

  S21Matrix matrix_before = test_matrix;
  S21Matrix result;

  EXPECT_NO_THROW(result = test_matrix.CalcComplements());
  EXPECT_TRUE(test_matrix == matrix_before);

  EXPECT_EQ(result.GetRows(), 1);
  EXPECT_EQ(result.GetCols(), 1);
  EXPECT_EQ(result(0, 0), 1.0);
}

TEST(TestCalcComplements, TestCalcComplementsOne2) {
  S21Matrix test_matrix(1, 1);

  EXPECT_EQ(test_matrix.GetRows(), 1);
  EXPECT_EQ(test_matrix.GetCols(), 1);

  test_matrix(0, 0) = 5.0;
  S21Matrix matrix_before = test_matrix;
  S21Matrix result;

  EXPECT_NO_THROW(result = test_matrix.CalcComplements());
  EXPECT_TRUE(test_matrix == matrix_before);

  EXPECT_EQ(result.GetRows(), 1);
  EXPECT_EQ(result.GetCols(), 1);
  EXPECT_EQ(result(0, 0), 1.0);
}

TEST(TestCalcComplements, TestCalcComplementsZero1) {
  S21Matrix matrix1{3, 3};
  EXPECT_EQ(matrix1.GetCols(), 3);
  EXPECT_EQ(matrix1.GetRows(), 3);

  S21Matrix result_check{3, 3};
  EXPECT_EQ(result_check.GetCols(), 3);
  EXPECT_EQ(result_check.GetRows(), 3);

  matrix1(0, 0) = -3.00;
  matrix1(0, 1) = 6.00;
  matrix1(0, 2) = -3.00;
  matrix1(1, 0) = 6.00;
  matrix1(1, 1) = -12.00;
  matrix1(1, 2) = 6.00;
  matrix1(2, 0) = -3.00;
  matrix1(2, 1) = 6.00;
  matrix1(2, 2) = -3.00;

  S21Matrix matrix_before = matrix1;
  S21Matrix result = matrix1.CalcComplements();

  EXPECT_TRUE(result == result_check);
  EXPECT_TRUE(matrix1 == matrix_before);
}

TEST(TestCalcComplements, TestCalcComplementsZero2) {
  S21Matrix matrix1{3, 3};
  EXPECT_EQ(matrix1.GetCols(), 3);
  EXPECT_EQ(matrix1.GetRows(), 3);

  S21Matrix result_check{3, 3};
  EXPECT_EQ(result_check.GetCols(), 3);
  EXPECT_EQ(result_check.GetRows(), 3);

  S21Matrix matrix_before = matrix1;
  S21Matrix result = matrix1.CalcComplements();

  EXPECT_TRUE(result == result_check);
  EXPECT_TRUE(matrix1 == matrix_before);
}

TEST(TestCalcComplements, TestCalcComplementsZero3) {
  S21Matrix matrix1{3, 3};
  EXPECT_EQ(matrix1.GetCols(), 3);
  EXPECT_EQ(matrix1.GetRows(), 3);

  S21Matrix result_check{3, 3};
  EXPECT_EQ(result_check.GetCols(), 3);
  EXPECT_EQ(result_check.GetRows(), 3);

  matrix1(0, 0) = 0.00;
  matrix1(0, 1) = 9.00;
  matrix1(0, 2) = 0.0;
  matrix1(1, 0) = 0.00;
  matrix1(1, 1) = -12.00;
  matrix1(1, 2) = 0.0;
  matrix1(2, 0) = 0.00;
  matrix1(2, 1) = 7.00;
  matrix1(2, 2) = 0.00;

  S21Matrix matrix_before = matrix1;
  S21Matrix result = matrix1.CalcComplements();

  EXPECT_TRUE(result == result_check);
  EXPECT_TRUE(matrix1 == matrix_before);
}
int lin(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
