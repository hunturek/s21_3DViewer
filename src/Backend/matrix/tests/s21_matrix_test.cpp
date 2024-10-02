/* Copyright [2024] <Casscurs> */

#include "./s21_matrix_test.hpp"

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);

  S21Matrix aboba(5, 5);
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      aboba(i, j) = 1;
    }
  }
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      std::cout << aboba(i, j) << " ";
    }
    std::cout << "\n";
  }
  return RUN_ALL_TESTS();
}
