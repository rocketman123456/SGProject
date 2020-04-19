cmake_minimum_required (VERSION 3.8)

add_executable (pthread_test "pthread_test.cpp")
target_link_libraries (pthread_test libpthreadVCE3d.lib)
