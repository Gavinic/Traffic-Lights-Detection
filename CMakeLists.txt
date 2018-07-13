cmake_minimum_required(VERSION 3.0.0)
project(Traffic_lights)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Opencv3 required 
set(OpenCV_DIR /usr/local/lib)
#find_package(OpenCV REQUIRED)
find_package(OpenCV 3.3.0 REQUIRED)

#where to find header files
include_directories(.)
include_directories(include)
include_directories(${OpenCV_INCLUDE_DIRS})

#source to be compiled
set(SOURCE_FILES
        src/lights_locate.cpp
        src/lights_recognize.cpp
        src/lights_detect.cpp
        src/lights_judge.cpp
        src/feature.cpp
        src/core_fun.cpp
        src/test.cpp
        util/util.cpp
        train/svm_train.cpp
        )

# pack objects to static library
add_library(Traffic_lights STATIC ${SOURCE_FILES})  
if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    set(EXECUTABLE_NAME "demo")       
endif()

#test case
add_executable(${EXECUTABLE_NAME} test/main.cpp)  

# link opencv libs
target_link_libraries(${EXECUTABLE_NAME} Traffic_lights ${OpenCV_LIBS})
MESSAGE(${CMAKE_BINARY_DIR}/../)
#ET_TARGET_PROPERTIES(${EXECUTABLE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY  "${CMAKE_BINARY_DIR}/../")
