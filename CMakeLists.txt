cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(runtests C)

include_directories("." "PJ/inc")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -W -Wall -Wextra -Werror")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wmissing-prototypes")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wold-style-definition")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pedantic")

set(PJTEST_SRC_FILES
	runtests.c
	fileio/test_filepath.c
	util/test_dlist.c
	util/test_pjassert.c
	util/test_slist.c
	util/test_textutil.c
	)

set(PJPAINT_SRC_FILES
	PJ/fileio/filepath.c
	PJ/util/dlist.c
	PJ/util/pjassert.c
	PJ/util/slist.c
	PJ/util/textutil.c
	)

add_executable(runtests WIN32
	${PJTEST_SRC_FILES}
	${PJPAINT_SRC_FILES})

target_link_libraries(runtests
	cunit)
