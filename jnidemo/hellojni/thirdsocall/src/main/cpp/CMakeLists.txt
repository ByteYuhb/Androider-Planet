# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.10.2)

# Declares and names the project.

project("myapplication1")

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.
aux_source_directory(${CMAKE_SOURCE_DIR} _SRC_FILES)
add_library( # Sets the name of the library.
             third-call-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
        ${_SRC_FILES} )

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

#调用第三方库的类库
target_link_libraries( # Specifies the target library.
                        third-call-lib

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )
#将第三方库添加进来，设置第三个参数为IMPORTED
add_library(hellojni-lib
        SHARED
        IMPORTED)
#设置第三方库的路径：IMPORTED_LOCATION
set_target_properties(hellojni-lib PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/../jniLibs/${ANDROID_ABI}/libhello-jni.so
        )
#设置调用库的include文件夹
target_include_directories(
        third-call-lib
        PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)
#将第三方库链接到调用库中
target_link_libraries( # Specifies the target library.
        third-call-lib

        # Links the target library to the log library
        # included in the NDK.
        hellojni-lib)



