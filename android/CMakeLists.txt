cmake_minimum_required(VERSION 3.9.0)
project(react-native-audio-context)

set (CMAKE_VERBOSE_MAKEFILE ON)
set (CMAKE_CXX_STANDARD 14)

add_library(react-native-audio-context
            SHARED
            ../cpp/JSIExampleHostObject.cpp
            cpp-adapter.cpp
)

# Specifies a path to native header files.
include_directories(
            ../cpp
            ../node_modules/react-native/ReactCommon/jsi
)

find_package(ReactAndroid REQUIRED CONFIG)

target_link_libraries(
  react-native-audio-context
  ReactAndroid::jsi
  android
)
