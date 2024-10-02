/* Copyright [2024] <Casscurs> */

#include "./s21_matrix_test.hpp"

TEST(Constructor_basic, test_1) {
  S21Matrix a;
  ASSERT_EQ(a.get_cols(), 0);
  ASSERT_EQ(a.get_rows(), 0);
}

TEST(Constructor_basic, test_2) {
  S21Matrix a;
  ASSERT_EQ(a.get_cols(), 0);
  ASSERT_EQ(a.get_rows(), 0);
  ASSERT_ANY_THROW(a(1, 2));
}

TEST(Constructor_param, test_1) {
  S21Matrix a(3, 3);
  ASSERT_EQ(a.get_rows(), 3);
  ASSERT_EQ(a.get_cols(), 3);
  a(2, 2) = 355.4532;
  ASSERT_DOUBLE_EQ(a(2, 2), 355.4532);
}

TEST(Constructor_param, test_2) {
  S21Matrix a(3, 5);
  ASSERT_EQ(a.get_rows(), 3);
  ASSERT_EQ(a.get_cols(), 5);
  a(2, 4) = 125.5;
  ASSERT_DOUBLE_EQ(a(2, 4), 125.5);
}

TEST(Constructor_param, test_3) { ASSERT_ANY_THROW(S21Matrix M(-2, 0)); }

TEST(Constructor_param, test_4) { ASSERT_ANY_THROW(S21Matrix M(-2, -2)); }

TEST(Constructor_param, test_5) { ASSERT_ANY_THROW(S21Matrix M(5, -2)); }

TEST(Constructor_param, test_6) {
  S21Matrix M(0, 0);
  ASSERT_EQ(M.get_rows(), 0);
  ASSERT_EQ(M.get_cols(), 0);
}

TEST(Constructor_copy, test_1) {
  S21Matrix M(5, 5);
  for (int i = 0; i < M.get_rows(); ++i) {
    for (int j = 0; j < M.get_cols(); ++j) {
      M(i, j) = 2;
    }
  }
  S21Matrix M2 = M;
  for (int i = 0; i < M.get_rows(); ++i) {
    for (int j = 0; j < M.get_cols(); ++j) {
      ASSERT_EQ(M(i, j), M2(i, j));
    }
  }
}

TEST(Constructor_move, test_1) {
  S21Matrix M(6, 6);
  for (int i = 0; i < M.get_rows(); i++) {
    for (int j = 0; j < M.get_cols(); ++j) {
      M(i, j) = 5;
    }
  }
  S21Matrix M2 = std::move(M);

  ASSERT_EQ(M2.get_rows(), 6);
  ASSERT_EQ(M2.get_cols(), 6);
  ASSERT_EQ(M.get_rows(), 0);
  ASSERT_EQ(M.get_cols(), 0);
}
