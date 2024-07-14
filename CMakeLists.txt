cmake_minimum_required(VERSION 3.29)

project(Eldorado CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_STANDARD 23)

file(
	DOWNLOAD
	https://github.com/cpm-cmake/CPM.cmake/releases/latest/download/CPM.cmake
	${CMAKE_CURRENT_SOURCE_DIR}/cmake/CPM.cmake
	EXPECTED_HASH SHA256=7b354f3a5976c4626c876850c93944e52c83ec59a159ae5de5be7983f0e17a2a
)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/CPM.cmake)

add_compile_options(-Wall -Wextra -Wpedantic)

CPMAddPackage(
	NAME googletest
	GITHUB_REPOSITORY google/googletest
	GIT_TAG main # gtest follows a live-at-head policy
	OPTIONS "INSTALL_GTEST OFF" "gtest_force_shared_crt ON" "BUILD_GMOCK OFF"
	EXCLUDE_FROM_ALL Yes
	SYSTEM Yes
)

if(BUILD_TESTING)
	set_property(GLOBAL PROPERTY CTEST_TARGETS_ADDED 1)
	include(CTest)
	enable_testing()
endif()

CPMAddPackage(
	NAME raylib
	GITHUB_REPOSITORY raysan5/raylib
	GIT_TAG 5.0
	EXCLUDE_FROM_ALL Yes
	SYSTEM Yes
)

if(raylib_ADDED)
	target_compile_options(raylib PRIVATE -w)
	target_compile_options(glfw PRIVATE -w)
endif()

CPMAddPackage(
	NAME curl
	GITHUB_REPOSITORY curl/curl
	GIT_TAG curl-8_8_0
	EXCLUDE_FROM_ALL Yes
	SYSTEM Yes
	OPTIONS
	"PICKY_COMPILER Off"
	"BUILD_CURL_EXE Off"
	"BUILD_SHARED_LIBS Off"
	"BUILD_STATIC_LIBS On"
	"CURL_DISABLE_INSTALL On"
	"BUILD_LIBCURL_DOCS Off"
	"BUILD_MISC_DOCS Off"
	"ENABLE_CURL_MANUAL Off"
	"CURL_ENABLE_SSL On"
	"CURL_USE_SCHANNEL On"
)

if(curl_ADDED)
	target_compile_options(libcurl_static PRIVATE -w)
	target_compile_options(libcurl_object PRIVATE -w)
endif()

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE
	src/main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	raylib
	Renderer
)

add_subdirectory(src/Cards)
add_subdirectory(src/Player)
add_subdirectory(src/Renderer)
add_subdirectory(src/Store)