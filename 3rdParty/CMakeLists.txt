cmake_minimum_required (VERSION 3.8)

add_library(GLAD
	src/glad.c
)

add_library(sqlite3
	src/sqlite3.c
)
