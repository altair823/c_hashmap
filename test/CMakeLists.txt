cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)    

file(GLOB SOURCES
		"${PROJECT_SOURCE_DIR}/src/*.c"
        )

add_executable(hashmap_test hashmap_test.c ${SOURCES})
target_include_directories(hashmap_test PUBLIC ../include)

