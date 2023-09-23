cmake_minimum_required(VERSION 3.7)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
project(SHCLogo)

if(CMAKE_CROSSCOMPILING AND CMAKE_SYSTEM_NAME STREQUAL "Windows")
	message(STATUS "Cross compiling: Unix->Windows")
	set(CMAKE_C_COMPILER  x86_64-w64-mingw32-gcc)
	set(CMAKE_CXX_COMPILER  x86_64-w64-mingw32-g++)

	set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
	set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
	set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
endif()

if(RELEASE)
	message(STATUS "Stripping symbols and debug info")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s")
else()
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
endif()

if(LEGACY)
	message(STATUS "Making legacy build")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DRETRO_MOD_LOADER_VER=1")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DRETRO_MOD_LOADER_VER=1")
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
set(MOD_NAME SHCLogo CACHE STRING "Used as root directory for mod source + logic file name")

add_library(SHCLogo SHARED
	GameAPI/C/GameAPI/Game.c
	${MOD_NAME}/dllmain.c
	${MOD_NAME}/LogoSetup.c
	${MOD_NAME}/SHCLogo.c
)

target_include_directories(SHCLogo PRIVATE
	GameAPI/C/
	${MOD_NAME}/
)

if(ANDROID)
	set_target_properties(SHCLogo PROPERTIES PREFIX "lib")
else()
	set_target_properties(SHCLogo PROPERTIES PREFIX "")
endif()

unset(MOD_NAME CACHE)
