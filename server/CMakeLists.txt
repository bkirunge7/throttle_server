cmake_minimum_required(VERSION 3.13) 
#CMake version check 
project(throttleserver) 
set(CMAKE_CXX_STANDARD 14) #Enable c++ 14 standard 
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-pthread")
#Add main.cpp file of project root directory as source file
set(SOURCE_FILES main.cpp UserQuota.cpp ThrottleServer.cpp RequestHandler.cpp TokenBucket.cpp TokenProcessor.cpp)
set(CLIENT_SOURCE_FILES generate_throttle_request.cpp)
#Add executable target with source files listed in SOURCE_FILES variable
add_executable(throttleserver ${SOURCE_FILES})
add_executable(generate_throttle_request ${CLIENT_SOURCE_FILES})
