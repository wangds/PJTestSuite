cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(runtests C)

include_directories("." "PJ/inc")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -W -Wall -Wextra -Werror")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wmissing-prototypes")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wold-style-definition")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pedantic")

set(PJTEST_SRC_FILES
	runtests.c
	util/test_pjassert.c
	)

set(PJPAINT_SRC_FILES
	PJ/util/pjassert.c
	)

add_executable(runtests WIN32
	${PJTEST_SRC_FILES}
	${PJPAINT_SRC_FILES})

target_link_libraries(runtests
	cunit)
