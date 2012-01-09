#	---------------------------------------------------------------------------------------
# 	2010 Nik Karpinsky
#	LGPL 2010
#
#	Reactor Library for C++
#	---------------------------------------------------------------------------------------

set(NAME reactor)

### ---------------------------------------------------------------------------------------
# Configure Dependencies
### ---------------------------------------------------------------------------------------
find_package(FFMPEG REQUIRED)
include_directories(${FFMPEG_INCLUDE_DIRS})
set(REACTOR_INCLUDE_DIRS ${REACTOR_INCLUDE_DIRS} ${FFMPEG_INCLUDE_DIRS})
set(REACTOR_LIBRARIES ${REACTOR_LIBRARIES} ${FFMPEG_LIBRARIES})

#	---------------------------------------------------------------------------------------
#	List all of the sources to be compiled
#	---------------------------------------------------------------------------------------

set(SOURCES	
	VideoFileReader.cpp
	VideoFileReader.h
)

source_group("reactor" FILES ${SOURCES})
include_directories(..)

#	---------------------------------------------------------------------------------------
#	Build Documentation
#	---------------------------------------------------------------------------------------
option(REACTOR_GENERATE_DOC "Build Doxygen Documentation" OFF)
if(REACTOR_GENERATE_DOC)
	add_subdirectory(../../doc ${PROJECT_BINARY_DIR}/doc)
endif(REACTOR_GENERATE_DOC)

#	---------------------------------------------------------------------------------------
#	Build the library
#	---------------------------------------------------------------------------------------

set(REACTOR_INCLUDE_DIRS ${REACTOR_INCLUDE_DIRS} PARENT_SCOPE)
set(REACTOR_LIBRARIES ${REACTOR_LIBRARIES} PARENT_SCOPE)

add_library(${NAME} ${SOURCES})

