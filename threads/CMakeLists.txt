cmake_minimum_required(VERSION 3.16)
project(tiger_moth LANGUAGES C)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# add_library(airship_lib src/airship.c src/engine.c src/recruit.c src/supplies.c src/update_crew.c src/wait_pirates.c src/cannon.c)
# target_include_directories(airship_lib PUBLIC include)
# add_executable(tiger_moth main.c)
# target_link_libraries(tiger_moth PRIVATE airship_lib + threads)

add_executable(tiger_moth main.c src/airship.c src/engine.c src/recruit.c src/supplies.c src/update_crew.c src/wait_pirates.c src/cannon.c)
target_include_directories(tiger_moth PRIVATE include)

target_compile_options(tiger_moth PRIVATE -Wall -Wextra -Werror -pedantic -pthread)
find_package(Threads REQUIRED)
target_link_libraries(tiger_moth PRIVATE Threads::Threads)
