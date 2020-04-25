cmake_minimum_required (VERSION 3.8)

add_library(SGLog
	SGLog.cpp
)
target_link_libraries(SGLog
	spdlog::spdlog spdlog::spdlog_header_only
)
