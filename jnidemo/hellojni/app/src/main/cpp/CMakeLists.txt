# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.10.2)

# Declares and names the project.

project("hellojni")

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
             native-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             native-lib.cpp )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       native-lib

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )

#1.在cpp中创建一个src文件夹，并在该文件夹下创建hellojni.cpp文件
#2.在cpp中创建一个include文件夹，并在该文件夹下创建hellojni.h头文件
message("CMAKE_SOURCE_DIR:")
message(${CMAKE_SOURCE_DIR})
    #为了演示此处使用动态注册方式
#3.创建一个新的库
add_library(
        hello-jni #库名
        SHARED #设置为so共享库
        src/hellojni.cpp
)
target_include_directories(hello-jni #库名
        PUBLIC
        include/hellojni.h)

target_link_libraries(hello-jni

        ${log-lib})


target_link_libraries(native-lib
        hello-jni)




