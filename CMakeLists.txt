cmake_minimum_required(VERSION 3.28)
project(guesser)

set(CMAKE_CXX_STANDARD 23)

add_executable(guesser main.cpp
        utilities/random.cpp
        classes/TestFile.cpp
        classes/TestFile.hpp
)
add_executable(testFileGenerator testFile/testFileGenerator.cpp utilities/random.cpp
        classes/TestFile.cpp
        classes/TestFile.hpp
)
add_executable(testFileSampler testFile/testFileSampler.cpp
        classes/TestFile.cpp
        classes/TestFile.hpp
        utilities/random.cpp
)
add_executable(HLL hll.cpp
        classes/TestFile.cpp
        classes/TestFile.hpp
        utilities/random.cpp
)
target_link_libraries(HLL PRIVATE libcount.a)