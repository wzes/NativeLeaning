add_library( # Sets the name of the library.
        JNIDemo

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        src/main/jni/JNIDemo.cpp)
target_link_libraries(
        JNIDemo
        android
        log)