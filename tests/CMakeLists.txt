#Download an include Google Test

include (FetchContent)

#set(FETCHCONTENT_FULLY_DISCONNECTED ON)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

target_include_directories(Colorful_IO PRIVATE ${CMAKE_SOURCE_DIR}/include)

#Create Test Executable
add_executable(UnitTests main.cpp colorful_io_ut.cpp)
target_link_libraries(UnitTests PRIVATE Colorful_IO gtest_main)



#Register Tests
add_test(NAME UnitTests COMMAND UnitTests)


# Post-build step to copy the DLL into the same folder as the test binary
add_custom_command(TARGET UnitTests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Colorful_IO>                         # Full path to built DLL
        $<TARGET_FILE_DIR:UnitTests>                       # Destination dir (same as UnitTests binary)
)