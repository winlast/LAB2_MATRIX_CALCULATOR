#include <gtest/gtest.h>
#include "matrix.h"
#include <cmath> // для fabs

// Тест на создание и освобождение матрицы
TEST(MatrixTest, CreateAndFree) {
    Matrix m = create_matrix(3, 4);
    EXPECT_EQ(m.rows, 3);
    EXPECT_EQ(m.cols, 4);
    EXPECT_NE(m.data, nullptr);

    // Проверяем, что память инициализирована нулями
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            EXPECT_DOUBLE_EQ(m.data[i][j], 0.0);
        }
    }
    free_matrix(m);
    // После освобождения структура "пуста", но проверить это сложно из-за передачи по значению.
    // Лучше не полагаться на поля m после free_matrix.
}

// Тест на обработку ошибок при создании
TEST(MatrixTest, InvalidCreation) {
    EXPECT_THROW(create_matrix(0, 5), std::invalid_argument);
    EXPECT_THROW(create_matrix(-1, 5), std::invalid_argument);
    // Слишком большая матрица может привести к bad_alloc, но это нестабильный тест
}

// Тест сложения матриц
TEST(MatrixTest, Addition) {
    Matrix A = create_matrix(2, 2);
    Matrix B = create_matrix(2, 2);

    A.data[0][0] = 1.0; A.data[0][1] = 2.0;
    A.data[1][0] = 3.0; A.data[1][1] = 4.0;

    B.data[0][0] = 5.0; B.data[0][1] = 6.0;
    B.data[1][0] = 7.0; B.data[1][1] = 8.0;

    Matrix result = matrix_add(A, B);

    EXPECT_DOUBLE_EQ(result.data[0][0], 6.0);
    EXPECT_DOUBLE_EQ(result.data[0][1], 8.0);
    EXPECT_DOUBLE_EQ(result.data[1][0], 10.0);
    EXPECT_DOUBLE_EQ(result.data[1][1], 12.0);

    free_matrix(A);
    free_matrix(B);
    free_matrix(result);
}

// Тест на ошибку при сложении
TEST(MatrixTest, AdditionSizeMismatch) {
    Matrix A = create_matrix(2, 2);
    Matrix B = create_matrix(3, 3);

    EXPECT_THROW(matrix_add(A, B), std::invalid_argument);

    free_matrix(A);
    free_matrix(B);
}

// Тест умножения матриц
TEST(MatrixTest, Multiplication) {
    Matrix A = create_matrix(2, 3);
    Matrix B = create_matrix(3, 2);

    // Заполняем A: [1, 2, 3]
    //              [4, 5, 6]
    double counter = 1.0;
    for (int i = 0; i < A.rows; i++) {
        for (int j = 0; j < A.cols; j++) {
            A.data[i][j] = counter++;
        }
    }
    // Заполняем B: [7, 8]
    //              [9, 10]
    //              [11, 12]
    for (int i = 0; i < B.rows; i++) {
        for (int j = 0; j < B.cols; j++) {
            B.data[i][j] = 7.0 + i * B.cols + j;
        }
    }

    Matrix result = matrix_multiply(A, B);

    // Ожидаемый результат: [58, 64]
    //                      [139, 154]
    EXPECT_DOUBLE_EQ(result.data[0][0], 58.0);
    EXPECT_DOUBLE_EQ(result.data[0][1], 64.0);
    EXPECT_DOUBLE_EQ(result.data[1][0], 139.0);
    EXPECT_DOUBLE_EQ(result.data[1][1], 154.0);

    free_matrix(A);
    free_matrix(B);
    free_matrix(result);
}

// Тест транспонирования
TEST(MatrixTest, Transpose) {
    Matrix A = create_matrix(2, 3);
    A.data[0][0] = 1; A.data[0][1] = 2; A.data[0][2] = 3;
    A.data[1][0] = 4; A.data[1][1] = 5; A.data[1][2] = 6;

    Matrix T = matrix_transpose(A);

    EXPECT_EQ(T.rows, 3);
    EXPECT_EQ(T.cols, 2);
    EXPECT_DOUBLE_EQ(T.data[0][0], 1.0);
    EXPECT_DOUBLE_EQ(T.data[0][1], 4.0);
    EXPECT_DOUBLE_EQ(T.data[1][0], 2.0);
    EXPECT_DOUBLE_EQ(T.data[1][1], 5.0);
    EXPECT_DOUBLE_EQ(T.data[2][0], 3.0);
    EXPECT_DOUBLE_EQ(T.data[2][1], 6.0);

    free_matrix(A);
    free_matrix(T);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}