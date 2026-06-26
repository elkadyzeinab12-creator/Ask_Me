cmake_minimum_required(VERSION 4.0)
project(ASK_me)

set(CMAKE_CXX_STANDARD 20)

add_executable(ASK_me main.cpp
        question.cpp
        question.h
        user.cpp
        user.h
        utils.cpp
        utils.h
        AskMeManager.cpp
        AskMeManager.h
)
