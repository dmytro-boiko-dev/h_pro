add_library(gate STATIC gate.cpp) # static lib
add_library(counter SHARED counter.cpp)  # dynamic lib

target_include_directories(gate PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(counter PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(gate PRIVATE counter)  # link dynamic library to gate

# fix: copy DLL to executable directory after building
add_custom_command(TARGET counter POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:counter> ${CMAKE_BINARY_DIR}/src)