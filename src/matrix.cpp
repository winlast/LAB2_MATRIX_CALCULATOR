#include "matrix.h"
#include <iostream>  // для std::cerr в тестах, можно убрать
#include <iomanip>   // для print_matrix
#include <stdexcept> // для std::invalid_argument, std::bad_alloc

Matrix create_matrix(int rows, int cols) {
    // 1. Проверка корректности размеров
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Matrix dimensions must be positive integers");
    }

    Matrix mat;
    mat.rows = rows;
    mat.cols = cols;

    // 2. Выделение памяти для массива указателей на строки
    mat.data = new double*[rows];
    if (mat.data == nullptr) {
        throw std::bad_alloc();
    }

    // 3. Выделение памяти для каждой строки и инициализация нулями
    for (int i = 0; i < rows; i++) {
        mat.data[i] = new double[cols];
        if (mat.data[i] == nullptr) {
            // Освобождаем уже выделенную память при ошибке
            for (int j = 0; j < i; j++) {
                delete[] mat.data[j];
            }
            delete[] mat.data;
            throw std::bad_alloc();
        }
        // Инициализация нулями
        for (int j = 0; j < cols; j++) {
            mat.data[i][j] = 0.0;
        }
    }
    return mat;
}

void free_matrix(Matrix m) {
    // 1. Проверка на nullptr - защита от двойного освобождения
    if (m.data == nullptr) {
        return;
    }

    // 2. Освобождение памяти каждой строки
    for (int i = 0; i < m.rows; i++) {
        if (m.data[i] != nullptr) {
            delete[] m.data[i];
            // m.data[i] = nullptr; // Опционально, но структура m всё равно будет уничтожена
        }
    }

    // 3. Освобождение массива указателей
    delete[] m.data;

    // 4. Обнуление структуры (защита от use-after-free)
    // Это не имеет сильного эффекта, так как m передается по значению и является копией.
    // Для полной безопасности лучше передавать Matrix по указателю или ссылке (Matrix* m).
    // m.data = nullptr;
    // m.rows = 0;
    // m.cols = 0;
}

Matrix matrix_add(Matrix a, Matrix b) {
    // Проверка совместимости размеров
    if (a.rows != b.rows || a.cols != b.cols) {
        throw std::invalid_argument("Matrix dimensions must match for addition");
    }

    Matrix result = create_matrix(a.rows, a.cols);

    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            result.data[i][j] = a.data[i][j] + b.data[i][j];
        }
    }
    return result;
}

Matrix matrix_multiply(Matrix a, Matrix b) {
    // Проверка совместимости размеров
    if (a.cols != b.rows) {
        throw std::invalid_argument("Number of columns in A must equal number of rows in B for multiplication");
    }

    Matrix result = create_matrix(a.rows, b.cols);

    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < b.cols; j++) {
            result.data[i][j] = 0.0;
            for (int k = 0; k < a.cols; k++) {
                result.data[i][j] += a.data[i][k] * b.data[k][j];
            }
        }
    }
    return result;
}

Matrix matrix_transpose(Matrix m) {
    Matrix result = create_matrix(m.cols, m.rows);

    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            result.data[j][i] = m.data[i][j];
        }
    }
    return result;
}

void print_matrix(Matrix m) {
    // 1. Проверка валидности матрицы
    if (m.data == nullptr || m.rows <= 0 || m.cols <= 0) {
        std::cout << "[Empty matrix]" << std::endl;
        return;
    }

    // 2. Настройка формата вывода
    std::cout << std::fixed << std::setprecision(2);

    // 3. Определение, нужно ли сокращать вывод
    const int MAX_ROWS_TO_SHOW = 10;
    const int MAX_COLS_TO_SHOW = 8;
    bool show_summary = (m.rows > MAX_ROWS_TO_SHOW) || (m.cols > MAX_COLS_TO_SHOW);
    int rows_to_show = show_summary ? MAX_ROWS_TO_SHOW : m.rows;
    int cols_to_show = show_summary ? MAX_COLS_TO_SHOW : m.cols;

    // 4. Вывод матрицы
    for (int i = 0; i < rows_to_show; i++) {
        // Пропуск средних строк для больших матриц
        if (show_summary && i == MAX_ROWS_TO_SHOW / 2 && m.rows > MAX_ROWS_TO_SHOW) {
            std::cout << "[...";
            for (int j = 0; j < cols_to_show - 2; j++) {
                std::cout << "      "; // 6 пробелов под число
            }
            std::cout << "...]" << std::endl;
            continue;
        }

        std::cout << "[ "; // Открывающая скобка

        // Вывод элементов строки
        for (int j = 0; j < cols_to_show; j++) {
            // Пропуск средних столбцов для больших матриц
            if (show_summary && j == MAX_COLS_TO_SHOW / 2 && m.cols > MAX_COLS_TO_SHOW) {
                std::cout << "... ";
                continue;
            }
            std::cout << std::setw(6) << m.data[i][j]; // Выравнивание
            if (j < cols_to_show - 1) {
                std::cout << " "; // Пробел между элементами
            }
        }

        std::cout << " ]"; // Закрывающая скобка

        // Добавление многоточия если пропущены столбцы
        if (show_summary && m.cols > MAX_COLS_TO_SHOW) {
            std::cout << " ...";
        }
        std::cout << std::endl;
    }

    // 5. Добавление многоточия если пропущены строки
    if (show_summary && m.rows > MAX_ROWS_TO_SHOW) {
        std::cout << "[... ... ...]" << std::endl;
    }

    // 6. Информация о размере если матрица большая
    if (show_summary) {
        std::cout << "Matrix " << m.rows << "×" << m.cols
                  << " (showing first " << rows_to_show << "×" << cols_to_show << ")"
                  << std::endl;
    }
}

Matrix matrix_from_array(double* data, int rows, int cols) {
    Matrix mat = create_matrix(rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // Копируем данные построчно из одномерного массива
            mat.data[i][j] = data[i * cols + j];
        }
    }
    return mat;
}