add_executable(regex1 regex1.c)

target_link_libraries(regex1 cregreslib m)

add_executable(regex2 regex2.c)

target_link_libraries(regex2 cregreslib m)

add_executable(regex3 regex3.c)

target_link_libraries(regex3 cregreslib m)

add_executable(regex4 regex4.c)

target_link_libraries(regex4 cregreslib m)

add_executable(regex5 regex5.c)

target_link_libraries(regex5 cregreslib m)

set_target_properties(regex1 regex2 regex3 regex4 regex5
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/test"
)
