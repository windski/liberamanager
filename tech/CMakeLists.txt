PROJECT(liberamanager)

SET(SRC_LIST main.c book.c book.h)

if(WIN32 AND MINGW)
	set(CMAKE_C_FLAGS "-finput-charset=UTF-8 -fexec-charset=GBK ${CMAKE_C_FLAGS}")
	message(STATUS "optional: -finput-charset=UTF-8 -fexec-charset=GBK")
endif()

ADD_EXECUTABLE(tech ${SRC_LIST})

