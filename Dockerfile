# Используем официальный образ GCC
FROM gcc:12.2.0

# Установка зависимостей (doxygen, graphviz, cmake для сборки gtest)
RUN apt-get update && apt-get install -y \
    doxygen \
    graphviz \
    cmake \
    && rm -rf /var/lib/apt/lists/*

# Создаем и переходим в рабочую директорию
WORKDIR /app

# Копируем исходный код в контейнер
COPY src/ ./src/
COPY Doxyfile ./

# Устанавливаем и собираем Google Test
RUN apt-get update && apt-get install -y libgtest-dev cmake make
RUN cd /usr/src/gtest && \
    cmake CMakeLists.txt && \
    make && \
    cp lib/*.a /usr/lib && \
    cd /app

# Компилируем приложения
RUN g++ -std=c++17 -o matrix_app src/matrix.cpp src/main.cpp
RUN g++ -std=c++17 -pthread -o test_app src/matrix.cpp src/test.cpp -lgtest -lgtest_main

# Генерируем документацию (опционально, для проверки)
RUN doxygen Doxyfile

# Указываем команду по умолчанию (запуск тестов)
CMD ["./test_app"]