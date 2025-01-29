add_library(tasks STATIC tasks.cpp)

target_link_libraries(tasks PRIVATE vector)

target_include_directories(tasks PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
