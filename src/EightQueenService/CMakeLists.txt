cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 17)
project("EightQueen" LANGUAGES CXX)

set(AWS_LAMBDA_CMAKE $ENV{HOME}/out)
set(CMAKE_PREFIX_PATH "${AWS_LAMBDA_CMAKE};${CMAKE_PREFIX_PATH}")

find_package(aws-lambda-runtime REQUIRED)
find_package(AWSSDK COMPONENTS core)

add_executable(${PROJECT_NAME} "main.cpp" "EightQueen.cpp")
target_link_libraries(${PROJECT_NAME} PRIVATE AWS::aws-lambda-runtime ${AWSSDK_LINK_LIBRARIES})
target_compile_features(${PROJECT_NAME} PRIVATE "cxx_std_17")
target_compile_options(${PROJECT_NAME} PRIVATE "-Wall" "-Wextra")

aws_lambda_package_target(${PROJECT_NAME})
