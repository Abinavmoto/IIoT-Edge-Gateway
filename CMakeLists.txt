cmake_minimum_required (VERSION 3.10)

# Define the project
project(MQTTPUB_CMAKE)

# Add definition for math library
add_library(conf common/config/src/conf_utils.c)
add_library(logutils common/log/src/log_utils.c )
add_library(mqtt common/mqtt/src/mqtt_utils.c)
add_library(utils common/utils/src/utils.c)

#set directory path for the BIN and LIB
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} )

# Add definition for the cmake-tutorial binary
add_executable(MQTTPUB_CMAKE iiot_gateway/src/iiot_gateway.c)
target_link_libraries(MQTTPUB_CMAKE conf mqtt logutils utils paho-mqtt3a config json-c)


# Locate GTest

find_package(GTest REQUIRED)
#find_package(GMock REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${GMOCK_INCLUDE_DIRS})

add_executable(runTest test/test_iiot_gateway.cpp)
target_link_libraries(runTest ${GMOCK_LIBRARIES} ${GTEST_LIBRARIES} pthread conf mqtt utils logutils paho-mqtt3a config json-c)
  

