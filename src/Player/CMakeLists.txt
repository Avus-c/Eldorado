project(Player)

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME} PRIVATE
	include/Player/player.hpp
	src/player.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(${PROJECT_NAME} PUBLIC
	Cards
)

if(BUILD_TESTING)
	add_executable(${PROJECT_NAME}_test)

	target_sources(${PROJECT_NAME}_test PRIVATE
		test/card_handling_test.cpp
	)

	target_link_libraries(${PROJECT_NAME}_test PRIVATE
		${PROJECT_NAME}
		gtest_main
	)

	add_test(NAME ${PROJECT_NAME}_test COMMAND ${PROJECT_NAME}_test)
endif()