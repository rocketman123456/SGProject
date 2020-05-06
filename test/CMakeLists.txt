cmake_minimum_required (VERSION 3.8)

add_executable (pthread_test "pthread_test.cpp")
target_link_libraries (pthread_test ${PTHREAD_LIBRARIES})

add_executable (sqlite_test "sqlite_test.cpp")
target_link_libraries (sqlite_test sqlite3)

add_executable (sg_time_test "sgtime_test.cpp")
target_link_libraries(sg_time_test SGTimeManager)

add_executable (event_test "event_test.cpp")
target_link_libraries (event_test SGMultiThread Utils SGLog)

add_executable (glm_test "glm_test.cpp")
target_link_libraries(glm_test Eigen3::Eigen)

add_executable (json_test "json_test.cpp")
target_link_libraries(json_test nlohmann_json nlohmann_json::nlohmann_json)

add_executable (fast_delegate_test "Demo.cpp")
