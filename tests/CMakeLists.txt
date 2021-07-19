find_package(Check REQUIRED)

find_package(Threads REQUIRED)

include(CheckCSourceCompiles)
include(CheckCSourceRuns)
include(CheckFunctionExists)
include(CheckIncludeFile)
include(CheckIncludeFiles)
include(CheckLibraryExists)
include(CheckSymbolExists)
include(CheckTypeSize)

include_directories(libft_tests)

file(GLOB_RECURSE unit_tests_src ${unit_tests_src} *.c)

add_executable(unit_exe ${unit_tests_src})

target_link_libraries(unit_exe libft ${CHECK_LIBRARIES} pthread)

add_test(NAME unit_exe COMMAND unit_exe WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/Testing)
