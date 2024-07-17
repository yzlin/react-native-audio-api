cmake_minimum_required(VERSION 3.9.0)
project(react-native-audio-context)

set (CMAKE_VERBOSE_MAKEFILE ON)
set (CMAKE_CXX_STANDARD 14)

include(../node_modules/react-native/ReactAndroid/cmake-utils/folly-flags.cmake)
add_compile_options(${folly_FLAGS})

include_directories(
        ../cpp
        ../cpp/AudioContext
        src/main/cpp
        ../node_modules/react-native/ReactCommon/jsi
        ../node_modules/react-native/ReactAndroid/src/main/jni/react/jni
        ../node_modules/react-native/ReactAndroid/src/main/jni/third-party/folly
)

add_library(react-native-audio-context SHARED
        src/main/cpp/OnLoad.cpp
        src/main/cpp/AudioContext
        src/main/cpp/OscillatorNode
        src/main/cpp/AudioDestinationNode

        ../cpp/OscillatorNodeHostObject
        ../cpp/AudioDestinationNodeHostObject

        ../cpp/AudioContext/AudioContextHostObject.h
        ../cpp/AudioContext/android
)

find_package(ReactAndroid REQUIRED CONFIG)
find_package(fbjni REQUIRED CONFIG)

target_link_libraries(react-native-audio-context
        ReactAndroid::jsi
        ReactAndroid::reactnativejni
        fbjni::fbjni
        ReactAndroid::folly_runtime
        android
        log
)
