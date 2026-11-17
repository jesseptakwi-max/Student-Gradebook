cmake_minimum_required(VERSION 3.16)
project(StudentGradeBook VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(gradebook_core
    src/Student.cpp src/Course.cpp src/Assessment.cpp src/GradeScale.cpp src/GradeBook.cpp)
target_include_directories(gradebook_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_options(gradebook_core PRIVATE -Wall -Wextra -Wpedantic)

add_executable(student_gradebook src/main.cpp)
target_link_libraries(student_gradebook PRIVATE gradebook_core)
target_compile_options(student_gradebook PRIVATE -Wall -Wextra -Wpedantic)

add_executable(gradebook_tests tests/test_main.cpp)
target_link_libraries(gradebook_tests PRIVATE gradebook_core)
target_compile_options(gradebook_tests PRIVATE -Wall -Wextra -Wpedantic)

enable_testing()
add_test(NAME gradebook_unit_tests COMMAND gradebook_tests)
