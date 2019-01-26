set(CMAKE_NO_SYSTEM_FROM_IMPORTED ON)

add_compile_options("-fexceptions" "-Os")

add_subdirectory(main)

target_link_libraries(${PROJECT_NAME} main)

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${ELF2BIN} -O binary $<TARGET_FILE:${CMAKE_PROJECT_NAME}> $<TARGET_FILE:${CMAKE_PROJECT_NAME}>.bin
    COMMAND ${CMAKE_COMMAND} -E echo "-- built: $<TARGET_FILE:${CMAKE_PROJECT_NAME}>.bin")
