project(Cards)

add_library(${PROJECT_NAME} INTERFACE)

target_sources(${PROJECT_NAME} PRIVATE
	include/Cards/cards.hpp
)

target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)