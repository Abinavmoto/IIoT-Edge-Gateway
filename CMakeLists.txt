cmake_minimum_required (VERSION 3.10)

# Define the project
project(MQTTPUB_CMAKE)

# Add definition for math library
add_library(conf common/config/src/conf_utils.c)
add_library(logger common/log/src/log_utils.c common/log/src/logger.c)
add_library(mqtt common/mqtt/src/mqtt_utils.c)
add_library(utils common/utils/src/utils.c)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )

# Add definition for the cmake-tutorial binary
add_executable(MQTTPUB_CMAKE iiot_gateway/src/iiot_gateway.c)
target_link_libraries(MQTTPUB_CMAKE conf logger mqtt utils paho-mqtt3a config json-c)