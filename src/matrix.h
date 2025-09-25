#ifndef MATRIX_H
#define MATRIX_H

/**
 * @brief Структура, представляющая матрицу.
 */
typedef struct {
    double** data; ///< Указатель на двумерный массив данных.
    int rows;      ///< Количество строк в матрице.
    int cols;      ///< Количество столбцов в матрице.
} Matrix;

// Базовые операции (создание/удаление)
/**
 * @brief Создает новую матрицу с заданными размерами.
 * @param rows Количество строк (должно быть > 0).
 * @param cols Количество столбцов (должно быть > 0).
 * @return Matrix Структура Matrix с выделенной памятью, инициализированная нулями.
 * @throws std::invalid_argument Если rows или cols <= 0.
 * @throws std::bad_alloc Если не удалось выделить память.
 */
Matrix create_matrix(int rows, int cols);

/**
 * @brief Освобождает память, занятую матрицей.
 * @param m Матрица, память которой нужно освободить.
 * @note Функция безопасна для вызова с уже освобожденной или неинициализированной матрицей.
 */
void free_matrix(Matrix m);

// Базовые арифметические операции
/**
 * @brief Выполняет сложение двух матриц.
 * @param a Первая матрица.
 * @param b Вторая матрица.
 * @return Matrix Новая матрица - результат сложения.
 * @throws std::invalid_argument Если размеры матриц не совпадают.
 */
Matrix matrix_add(Matrix a, Matrix b);

/**
 * @brief Выполняет умножение двух матриц.
 * @param a Первая матрица (размер MxN).
 * @param b Вторая матрица (размер NxK).
 * @return Matrix Новая матрица - результат умножения (размер MxK).
 * @throws std::invalid_argument Если количество столбцов матрицы A не равно количеству строк матрицы B.
 */
Matrix matrix_multiply(Matrix a, Matrix b);

/**
 * @brief Транспонирует матрицу.
 * @param m Исходная матрица.
 * @return Matrix Новая матрица - результат транспонирования.
 */
Matrix matrix_transpose(Matrix m);

// Вспомогательные функции
/**
 * @brief Выводит матрицу в консоль в форматированном виде.
 * @param m Матрица для вывода.
 */
void print_matrix(Matrix m);

/**
 * @brief Создает матрицу из одномерного массива данных.
 * @param data Указатель на одномерный массив данных (размера rows * cols).
 * @param rows Количество строк.
 * @param cols Количество столбцов.
 * @return Matrix Новая матрица, заполненная данными из массива.
 * @note Данные копируются построчно из массива в матрицу.
 */
Matrix matrix_from_array(double* data, int rows, int cols);

#endif // MATRIX_H