

# Устанавливаем минимальную версию CMake
cmake_minimum_required(VERSION 3.10)

# Название проекта
project(SearchEngine)

# Путь к директории с заголовками
include_directories(${CMAKE_SOURCE_DIR}/include)

# Добавляем директорию для Google Test
add_subdirectory(C:\Users\maksimkonon\source\repos\SearchEngine\googletest)

# Файлы исходного кода
file(GLOB SOURCES "src/*.cpp")
file(GLOB TEST_SOURCES "tests/*.cpp")

# Создаем исполняемый файл SearchEngine
add_executable(SearchEngine ${SOURCES} ${TEST_SOURCES})

# Находим и связываем Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Связываем Google Test с тестами
target_link_libraries(SearchEngine gtest_main gmock)
