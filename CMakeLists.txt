cmake_minimum_required(VERSION 3.18.2)
project(Library VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


add_library(
  book-a
  Book.h
  Book.cpp
)


add_library(
  library-a
  Library.h
  Library.cpp
)


add_executable(${PROJECT_NAME} 
  main.cpp
)

target_link_libraries(
  ${PROJECT_NAME} 
  PRIVATE library-a
  PRIVATE book-a

)

