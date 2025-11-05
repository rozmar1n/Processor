cmake_minimum_required(VERSION 3.16)

project(MIPTProcessor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(PROJECT_SOURCE_DIR_ESCAPED "${CMAKE_CURRENT_SOURCE_DIR}")
string(REPLACE "\"" "\\\"" PROJECT_SOURCE_DIR_ESCAPED "${PROJECT_SOURCE_DIR_ESCAPED}")
set(PROJECT_SOURCE_DIR_LITERAL "\"${PROJECT_SOURCE_DIR_ESCAPED}\"")

add_library(onegin STATIC
    src/common/onegin/ForIndexes.cpp
)
target_include_directories(onegin
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_library(stack STATIC
    src/common/stack/Stack.cpp
)
target_include_directories(stack
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(my_compiler
    src/compiler/assembler.cpp
    src/compiler/commands.cpp
    src/compiler/main.cpp
)
target_include_directories(my_compiler
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(my_compiler
    PRIVATE
        onegin
)
target_compile_definitions(my_compiler
    PRIVATE
        PROJECT_SOURCE_DIR=${PROJECT_SOURCE_DIR_LITERAL}
)

add_executable(my_processor
    src/processor/main.cpp
    src/processor/processor.cpp
)
target_include_directories(my_processor
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(my_processor
    PRIVATE
        stack
)
if (UNIX)
    target_link_libraries(my_processor PRIVATE m)
endif()
target_compile_definitions(my_processor
    PRIVATE
        PROJECT_SOURCE_DIR=${PROJECT_SOURCE_DIR_LITERAL}
)

add_executable(circle_generator
    tools/circle_generator.cpp
)
target_compile_definitions(circle_generator
    PRIVATE
        PROJECT_SOURCE_DIR=${PROJECT_SOURCE_DIR_LITERAL}
)

include(CTest)
if (BUILD_TESTING)
    enable_testing()

    set(SAMPLE_PROGRAM ${CMAKE_CURRENT_SOURCE_DIR}/tests/programs/add.txt)
    set(SAMPLE_BINARY  ${CMAKE_BINARY_DIR}/sample_add.bin)

    add_test(NAME compile_sample_program
        COMMAND $<TARGET_FILE:my_compiler> ${SAMPLE_PROGRAM} ${SAMPLE_BINARY})

    add_test(NAME run_sample_program
        COMMAND $<TARGET_FILE:my_processor> ${SAMPLE_BINARY})
    set_tests_properties(run_sample_program PROPERTIES
        DEPENDS compile_sample_program
        PASS_REGULAR_EXPRESSION "OUT: 5")
endif()
