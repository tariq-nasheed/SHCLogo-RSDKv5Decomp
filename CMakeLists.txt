cmake_minimum_required(VERSION 3.7)
project(SHCLogo)

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
