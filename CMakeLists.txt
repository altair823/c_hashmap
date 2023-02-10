cmake_minimum_required(VERSION 3.16)

project(c_hashmap)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCE
	"${PROJECT_SOURCE_DIR}/src/*c"
    )
add_executable(c_hashmap main.c ${SOURCE}) 
target_include_directories(c_hashmap PUBLIC include)

add_subdirectory(test)


enable_testing()
add_test(NAME hash_test COMMAND hash_test)

