cmake_minimum_required(VERSION 3.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(pss)

if(UNIX)
set(ACE_ROOT C:\Tools\ACE-6.3.0\ACE_wrappers)
else()
set(ACE_ROOT /root/Tools/ACE_wrappers)
endif()
#3rd cmake modules
#list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

#check cxx flag in linux system
if(UNIX)
	#linux
	include(CheckCXXCompilerFlag)
	CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
	if(COMPILER_SUPPORTS_CXX11)
	    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	endif()
endif()

########################################################################

set(ROOT_DIR ${PROJECT_SOURCE_DIR})

if(UNIX)
include_directories(
    #TODO:include dir
	${ACE_ROOT}/
	${ROOT_DIR}/purenessscopeserver/Common
	${ROOT_DIR}/purenessscopeserver/FrameCore/Common
	${ROOT_DIR}/purenessscopeserver/FrameCore/Console
	${ROOT_DIR}/purenessscopeserver/FrameCore/LogSystem
	${ROOT_DIR}/purenessscopeserver/FrameCore/Message
	${ROOT_DIR}/purenessscopeserver/FrameCore/PacketParse
	${ROOT_DIR}/purenessscopeserver/FrameCore/Reactor
	${ROOT_DIR}/purenessscopeserver/FrameCore/UDP
	${ROOT_DIR}/purenessscopeserver/FrameCore/TinyXML
	${ROOT_DIR}/purenessscopeserver/FrameCore/Mail
	${ROOT_DIR}/purenessscopeserver/FrameCore/FileTest
	${ROOT_DIR}/purenessscopeserver/FrameCore
)
else()
include_directories(
    #TODO:include dir
	${ACE_ROOT}/
	${ROOT_DIR}/purenessscopeserver/Common
	${ROOT_DIR}/purenessscopeserver/FrameCore/Common
	${ROOT_DIR}/purenessscopeserver/FrameCore/Console
	${ROOT_DIR}/purenessscopeserver/FrameCore/LogSystem
	${ROOT_DIR}/purenessscopeserver/FrameCore/Message
	${ROOT_DIR}/purenessscopeserver/FrameCore/PacketParse
	${ROOT_DIR}/purenessscopeserver/FrameCore/Reactor
	${ROOT_DIR}/purenessscopeserver/FrameCore/UDP
	${ROOT_DIR}/purenessscopeserver/FrameCore/TinyXML
	${ROOT_DIR}/purenessscopeserver/FrameCore/Mail
	${ROOT_DIR}/purenessscopeserver/FrameCore/FileTest
	${ROOT_DIR}/purenessscopeserver/FrameCore
)
endif()

if(UNIX)
    #linux
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g -ggdb -fPIC")
    if(CMAKE_BUILD_TYPE MATCHES "debug")
        set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -fPIC")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -D_DEBUG ")
    else()
        set(CMAKE_BUILD_TYPE "Release")
        set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -fPIC")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -DNDEBUG")
    endif()
    set(LDFLAGS "$ENV{LDFLAGS} -stdlib=libc++")
    #TODO:3rd lib dir
    #set(DEP_LIB_DIR ${ROOT_DIR}/dep/lib/ ${ROOT_DIR}/bin/lib/)
	set(DEP_LIB_DIR ${ACE_ROOT}/lib/)
    #TODO:output dir
    #set(BIN_OUTPUT_DIR ${ROOT_DIR}/bin/bin/)
    #TODO:plugin or lib output dir
    #set(LIB_OUTPUT_DIR ${ROOT_DIR}/bin/lib)
    add_definitions(-Wno-unused-variable -Wno-unused-parameter -Wno-unused-function -Wno-strict-aliasing -Wno-pmf-conversions)
    
    #OPTION:coverage
    #if(ENABLE_COVERAGE)
    #    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage")
    #endif()
    
else()
    #windows
    add_compile_options("/std:c++latest")
    set(DEP_LIB_DIR ${ACE_ROOT}/lib/)
    set(BIN_OUTPUT_DIR ${ROOT_DIR}/Build/Windows)
    add_definitions(
        -DWIN
        -D_WINDOWS
        -D_CRT_SECURE_NO_WARNINGS)
    if(CMAKE_BUILD_TYPE MATCHES "debug")
        add_definitions(-D_DEBUG)
    else(CMAKE_BUILD_TYPE MATCHES "debug")
        add_definitions(-DNDEBUG)
    endif(CMAKE_BUILD_TYPE MATCHES "debug")
    #TODO:put all out file in one directory
    #set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${LIB_OUTPUT_DIR}")
    #set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${LIB_OUTPUT_DIR}")
    #set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${LIB_OUTPUT_DIR}")
    #set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${LIB_OUTPUT_DIR}")
    #set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${LIB_OUTPUT_DIR}")
    #set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${LIB_OUTPUT_DIR}")
endif()

#TODO:lib link dir
#link_directories(${DEP_LIB_DIR})

#log
message("ROOT dir=${ROOT_DIR}")
#message("Bin Output dir=${BIN_OUTPUT_DIR}")
#message("DEP lib dir=${DEP_LIB_DIR}")
#message("Plugin Output=${LIB_OUTPUT_DIR}")
message("CMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}")

#codecov
#find_package(codecov)
##################################################################
message("Start to build all...")

#add your own sub dirs
add_subdirectory(purenessscopeserver)
#TODO:add other dirs