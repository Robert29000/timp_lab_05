cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(lab05)

add_library(banking STATIC Account.cpp Transaction.cpp)
