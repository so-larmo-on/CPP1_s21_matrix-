#include "test.h"

TEST(Technical, GetRows) {
  auto test1 = S21Matrix();
  EXPECT_EQ(test1.GetRows(), 0);
  auto test2 = S21Matrix(2, 2);
  EXPECT_EQ(test2.GetRows(), 2);
}

TEST(Technical, GetCols) {
  auto test1 = S21Matrix();
  EXPECT_EQ(test1.GetCols(), 0);
  auto test2 = S21Matrix(2, 2);
  EXPECT_EQ(test2.GetCols(), 2);
}

TEST(Technical, SetRows) {
  auto test1 = S21Matrix(1, 1);
  test1.SetRows(5);
  EXPECT_EQ(test1.GetRows(), 5);
  test1.SetRows(1);
}

TEST(Technical, SetCols) {
  auto test1 = S21Matrix(1, 1);
  test1.SetCols(5);
  EXPECT_EQ(test1.GetCols(), 5);
  test1.SetRows(1);
}

TEST(TestConst, TestConstructorMoveConst1) {
  S21Matrix matrix_test{14, 14};
  matrix_test.FillMatrix(2.0);

  const S21Matrix matrix_check = std::move(matrix_test);

  EXPECT_EQ(matrix_check.GetCols(), 14);
  EXPECT_EQ(matrix_check.GetRows(), 14);
  EXPECT_EQ(matrix_test.GetRows(), 0);
  EXPECT_EQ(matrix_test.GetCols(), 0);
  EXPECT_ANY_THROW(matrix_test(2, 2));
}

TEST(TestConst, TestEq1) {
  S21Matrix matrix1{1, 1};
  S21Matrix matrix2{1, 1};
  S21Matrix matrix3{1, 1};
  S21Matrix matrix4{1, 2};
  S21Matrix matrix5{2, 1};
  S21Matrix matrix6{2, 1};
  S21Matrix matrix7{2, 2};

  matrix1(0, 0) = -1.0;
  matrix2(0, 0) = 2.0;
  matrix3(0, 0) = 2.0;

  const S21Matrix matrix1_const = matrix1;
  const S21Matrix matrix2_const = matrix2;
  const S21Matrix matrix3_const = matrix3;
  const S21Matrix matrix4_const = matrix4;
  const S21Matrix matrix5_const = matrix5;
  const S21Matrix matrix6_const = matrix6;
  const S21Matrix matrix7_const = matrix7;

  EXPECT_FALSE(matrix1_const == matrix2_const);
  EXPECT_TRUE(matrix2_const == matrix3_const);
  EXPECT_FALSE(matrix3_const == matrix4_const);
  EXPECT_FALSE(matrix4_const == matrix5_const);
  EXPECT_TRUE(matrix5_const == matrix6_const);
  EXPECT_FALSE(matrix6_const == matrix7_const);
}

TEST(TestConst, TestOperatorBracketsConst1) {
  S21Matrix matrix_check{3, 3};
  EXPECT_EQ(matrix_check.GetRows(), 3);
  EXPECT_EQ(matrix_check.GetCols(), 3);

  ASSERT_NEAR(matrix_check(0, 0), 0.0, 1e-7);
  ASSERT_NEAR(matrix_check(0, 1), 0.0, 1e-7);
  ASSERT_NEAR(matrix_check(0, 2), 0.0, 1e-7);
  ASSERT_NEAR(matrix_check(1, 0), 0.0, 1e-7);
  ASSERT_NEAR(matrix_check(1, 1), 0.0, 1e-7);
  ASSERT_NEAR(matrix_check(1, 2), 0.0, 1e-7);
  ASSERT_NEAR(matrix_check(2, 0), 0.0, 1e-7);
  ASSERT_NEAR(matrix_check(2, 1), 0.0, 1e-7);
  ASSERT_NEAR(matrix_check(2, 2), 0.0, 1e-7);

  matrix_check(0, 0) = 1.0;
  matrix_check(0, 1) = 2.0;
  matrix_check(1, 0) = 3.0;
  matrix_check(1, 1) = 4.0;

  ASSERT_NEAR(matrix_check(0, 0), 1.0, 1e-7);
  ASSERT_NEAR(matrix_check(0, 1), 2.0, 1e-7);
  ASSERT_NEAR(matrix_check(0, 2), 0.0, 1e-7);
  ASSERT_NEAR(matrix_check(1, 0), 3.0, 1e-7);
  ASSERT_NEAR(matrix_check(1, 1), 4.0, 1e-7);
  ASSERT_NEAR(matrix_check(1, 2), 0.0, 1e-7);
  ASSERT_NEAR(matrix_check(2, 0), 0.0, 1e-7);
  ASSERT_NEAR(matrix_check(2, 1), 0.0, 1e-7);
  ASSERT_NEAR(matrix_check(2, 2), 0.0, 1e-7);

  const S21Matrix matrix_copy = matrix_check;

  ASSERT_NEAR(matrix_copy(0, 0), 1.0, 1e-7);
  ASSERT_NEAR(matrix_copy(0, 1), 2.0, 1e-7);
  ASSERT_NEAR(matrix_copy(0, 2), 0.0, 1e-7);
  ASSERT_NEAR(matrix_copy(1, 0), 3.0, 1e-7);
  ASSERT_NEAR(matrix_copy(1, 1), 4.0, 1e-7);
  ASSERT_NEAR(matrix_copy(1, 2), 0.0, 1e-7);
  ASSERT_NEAR(matrix_copy(2, 0), 0.0, 1e-7);
  ASSERT_NEAR(matrix_copy(2, 1), 0.0, 1e-7);
  ASSERT_NEAR(matrix_copy(2, 2), 0.0, 1e-7);
}

TEST(TestConst, TestSumConst1) {
  S21Matrix matrix1{2, 2};
  EXPECT_EQ(matrix1.GetCols(), 2);
  EXPECT_EQ(matrix1.GetRows(), 2);

  S21Matrix matrix2{2, 2};
  EXPECT_EQ(matrix2.GetCols(), 2);
  EXPECT_EQ(matrix2.GetRows(), 2);

  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;

  matrix2(0, 0) = 4;
  matrix2(0, 1) = 3;
  matrix2(1, 0) = 2;
  matrix2(1, 1) = 1;

  S21Matrix matrix2_before = matrix2;
  const S21Matrix matrix2_const = matrix2;
  matrix1.SumMatrix(matrix2_const);
  EXPECT_TRUE(matrix2_before == matrix2_const);
}
TEST(TestChain, TestChain1) {
  S21Matrix matrix1{1, 1};
  S21Matrix matrix2{2, 2};
  S21Matrix matrix3{3, 3};

  EXPECT_EQ((matrix1 = matrix2 = matrix3).GetCols(), matrix3.GetCols());
  EXPECT_TRUE(matrix1 == matrix3);
}

TEST(TestDefault, TestConstructorBasicConst1) {
  const S21Matrix matrix_check;
  EXPECT_EQ(matrix_check.GetRows(), 0);
  EXPECT_EQ(matrix_check.GetCols(), 0);
  EXPECT_ANY_THROW(S21Matrix matrix_wrong(-3, -4));
  EXPECT_ANY_THROW(S21Matrix matrix_wrong(3, -4));

  S21Matrix matrix1(1, 1);
  S21Matrix matrix_copy{matrix_check};
  EXPECT_EQ(matrix_copy.GetRows(), 0);
  EXPECT_EQ(matrix_copy.GetCols(), 0);

  S21Matrix matrix_move{std::move(matrix_check)};
  EXPECT_EQ(matrix_move.GetRows(), 0);
  EXPECT_EQ(matrix_move.GetCols(), 0);
}

TEST(TestDefault, TestAssignmentMove1) {
  S21Matrix matrix_test{5, 5};
  S21Matrix matrix_check;

  EXPECT_EQ(matrix_test.GetRows(), 5);
  EXPECT_EQ(matrix_test.GetCols(), 5);
  EXPECT_EQ(matrix_check.GetRows(), 0);
  EXPECT_EQ(matrix_check.GetCols(), 0);

  matrix_test = std::move(matrix_check);

  EXPECT_EQ(matrix_test.GetRows(), 0);
  EXPECT_EQ(matrix_test.GetCols(), 0);
  S21Matrix &&a = std::move(matrix_test);
  matrix_test = std::move(a);
  EXPECT_EQ(matrix_test.GetRows(), 0);
  EXPECT_EQ(matrix_test.GetCols(), 0);
}

TEST(TestThrow, TestSetGet) {
  S21Matrix matrix1(1, 2);
  EXPECT_ANY_THROW(matrix1.SetCols(-3));
  EXPECT_ANY_THROW(matrix1.SetRows(-3));
  EXPECT_NO_THROW(matrix1.SetCols(1));
  EXPECT_NO_THROW(matrix1.SetCols(1));
  EXPECT_NO_THROW(matrix1.SetCols(5));
  EXPECT_NO_THROW(matrix1.SetRows(5));
  EXPECT_NO_THROW(matrix1.SetRows(2));
  EXPECT_NO_THROW(matrix1.SetCols(2));
}

TEST(TestExtra, TestConstRef1) {
  S21Matrix result1 = S21Matrix(1, 1) + S21Matrix(1, 1);
  S21Matrix result2 = S21Matrix(1, 1) - S21Matrix(1, 1);
  S21Matrix result3 = S21Matrix(1, 1) * S21Matrix(1, 1);
  bool result4 = S21Matrix(1, 1) == S21Matrix(1, 1);
  S21Matrix result5 = S21Matrix(1, 1) * 2.0;
  S21Matrix result6 = 2.0 * S21Matrix(1, 1);

  S21Matrix result7(1, 1);
  result7 += S21Matrix(1, 1);
  S21Matrix result8(1, 1);
  result8 *= S21Matrix(1, 1);
  S21Matrix result9(1, 1);
  result9 -= S21Matrix(1, 1);
  S21Matrix result10(1, 1);
  result10 *= 3.0;

  EXPECT_TRUE(result1 == S21Matrix(1, 1));
  EXPECT_TRUE(result2 == S21Matrix(1, 1));
  EXPECT_TRUE(result3 == S21Matrix(1, 1));
  EXPECT_TRUE(result4);
  EXPECT_TRUE(result5 == S21Matrix(1, 1));
  EXPECT_TRUE(result6 == S21Matrix(1, 1));
  EXPECT_TRUE(result7 == S21Matrix(1, 1));
  EXPECT_TRUE(result8 == S21Matrix(1, 1));
  EXPECT_TRUE(result9 == S21Matrix(1, 1));
  EXPECT_TRUE(result10 == S21Matrix(1, 1));
}
TEST(OperatorsExceptions, Test1) {
  S21Matrix m(3, 3);
  S21Matrix m1(2, 2);
  S21Matrix result(2, 2);
  EXPECT_ANY_THROW(result = m1 + m);
  EXPECT_ANY_THROW(m1 += m);
  EXPECT_ANY_THROW(result = m1 - m);
  EXPECT_ANY_THROW(m1 -= m);
  EXPECT_ANY_THROW(result = m1 * m);
  EXPECT_ANY_THROW(m1 *= m);
}
TEST(TestGetMatrixElement, TestException) {
  S21Matrix matrix1(1, 2);
  EXPECT_ANY_THROW(matrix1(2, 1));
  EXPECT_ANY_THROW(matrix1(1, 3));
  EXPECT_ANY_THROW(matrix1(-1, 2));
  EXPECT_ANY_THROW(matrix1(1, -3));
}

int some(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}