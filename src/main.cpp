#include <iostream>
#include "matrix.h"

int main() {
    std::cout << "=== Matrix Calculator Demo ===" << std::endl;

    try {
        // 1. Создание матриц
        std::cout << "\n1. Creating matrices A and B..." << std::endl;
        Matrix A = create_matrix(2, 2);
        Matrix B = create_matrix(2, 2);

        // Заполнение данными
        A.data[0][0] = 1.0; A.data[0][1] = 2.0;
        A.data[1][0] = 3.0; A.data[1][1] = 4.0;

        B.data[0][0] = 5.0; B.data[0][1] = 6.0;
        B.data[1][0] = 7.0; B.data[1][1] = 8.0;

        std::cout << "Matrix A:" << std::endl;
        print_matrix(A);
        std::cout << "Matrix B:" << std::endl;
        print_matrix(B);

        // 2. Сложение
        std::cout << "\n2. Calculating A + B..." << std::endl;
        Matrix sum = matrix_add(A, B);
        print_matrix(sum);

        // 3. Умножение
        std::cout << "\n3. Calculating A * B..." << std::endl;
        Matrix product = matrix_multiply(A, B);
        print_matrix(product);

        // 4. Транспонирование
        std::cout << "\n4. Transposing A..." << std::endl;
        Matrix transposed = matrix_transpose(A);
        print_matrix(transposed);

        // 5. Создание из массива
        std::cout << "\n5. Creating matrix from array..." << std::endl;
        double arr[] = {9.0, 8.0, 7.0, 6.0, 5.0, 4.0};
        Matrix C = matrix_from_array(arr, 2, 3);
        print_matrix(C);

        // 7. Демонстрация вычисления следа матрицы
        std::cout << "\n7. Calculating trace of matrix A..." << std::endl;
        try {
            double trace_A = matrix_trace(A);
            std::cout << "Trace of matrix A: " << trace_A << std::endl;
            
            // Создаем квадратную матрицу для демонстрации
            Matrix D = create_matrix(3, 3);
            D.data[0][0] = 1; D.data[0][1] = 2; D.data[0][2] = 3;
            D.data[1][0] = 4; D.data[1][1] = 5; D.data[1][2] = 6;
            D.data[2][0] = 7; D.data[2][1] = 8; D.data[2][2] = 9;
            
            std::cout << "Matrix D (3x3):" << std::endl;
            print_matrix(D);
            
            double trace_D = matrix_trace(D);
            std::cout << "Trace of matrix D: " << trace_D << " (1 + 5 + 9 = 15)" << std::endl;
            
            free_matrix(D);
    
        } catch (const std::exception& e) {
           std::cerr << "Error calculating trace: " << e.what() << std::endl;
        }

        // 6. Освобождение памяти
        std::cout << "\n6. Freeing memory..." << std::endl;
        free_matrix(A);
        free_matrix(B);
        free_matrix(sum);
        free_matrix(product);
        free_matrix(transposed);
        free_matrix(C);

        std::cout << "Demo completed successfully!" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}