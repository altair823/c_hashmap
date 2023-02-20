cmake_minimum_required(VERSION 3.16)

project(c_hashmap)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCE
	"${PROJECT_SOURCE_DIR}/src/*c"
    )

add_subdirectory(test)


enable_testing()
add_test(NAME hashmap_test COMMAND hashmap_test)

