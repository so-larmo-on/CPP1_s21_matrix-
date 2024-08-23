#include "test.h"

TEST(SimpleMathOperations, EqMatrix) {
  auto test1 = S21Matrix(3, 3);
  test1(1, 2) = 5;
  auto test2 = test1;
  EXPECT_TRUE(test1.EqMatrix(test2));
  EXPECT_TRUE(test1.EqMatrix(test2) == (test1 == test2));
  test2(1, 1) = 1;
  EXPECT_FALSE(test1.EqMatrix(test2));
  EXPECT_TRUE(test1.EqMatrix(test2) == (test1 == test2));
  auto test3 = S21Matrix(5, 5);
  EXPECT_FALSE(test1.EqMatrix(test3));
  EXPECT_TRUE(test1.EqMatrix(test3) == (test1 == test3));
}

TEST(SimpleMathOperations, SumMatrixOnexOne) {
  auto test1 = S21Matrix(1, 1);
  test1(0, 0) = 1;
  auto test2 = test1;
  test1.SumMatrix(test2);
  EXPECT_EQ(test1(0, 0), 2);
}

TEST(SimpleMathOperations, SubMatrixOnexOne) {
  auto test1 = S21Matrix(1, 1);
  test1(0, 0) = 1;
  auto test2 = test1;
  test1.SubMatrix(test2);
  EXPECT_EQ(test1(0, 0), 0);
}

TEST(SimpleMathOperations, MulNumberOnexOne) {
  auto test1 = S21Matrix(1, 1);
  test1(0, 0) = 5;
  test1.MulNumber(3);
  EXPECT_EQ(test1(0, 0), 15);
}

TEST(SimpleMathOperations, MulMatrix) {
  auto test1 = S21Matrix(3, 3);
  for (int i = 0; i < test1.GetRows(); i++) {
    for (int j = 0; j < test1.GetCols(); j++) {
      test1(i, j) = test1.GetRows() * i + j + 1;
    }
  }
  auto test2 = test1;
  test1.MulMatrix(test2);
  test2(0, 0) = 30;
  test2(0, 1) = 36;
  test2(0, 2) = 42;
  test2(1, 0) = 66;
  test2(1, 1) = 81;
  test2(1, 2) = 96;
  test2(2, 0) = 102;
  test2(2, 1) = 126;
  test2(2, 2) = 150;
  EXPECT_EQ(test1, test2);
}

TEST(SimpleMathOperations, TestThrow) {
  S21Matrix matrix1(3, 2);
  S21Matrix matrix2(3, 1);

  EXPECT_ANY_THROW(matrix1.SumMatrix(matrix2));
  EXPECT_ANY_THROW(matrix1.SubMatrix(matrix2));
  EXPECT_ANY_THROW(matrix1.MulMatrix(matrix2));
  EXPECT_ANY_THROW(matrix1.CalcComplements());
  EXPECT_ANY_THROW(matrix1.InverseMatrix());
  EXPECT_ANY_THROW(matrix1.Determinant());

  S21Matrix matrix3(3, 3);
  matrix3.MakeFullMatrix(1, 1);
  EXPECT_ANY_THROW(matrix3.InverseMatrix());
}

int ari(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}