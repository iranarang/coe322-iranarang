cmake_minimum_required(VERSION 3.17)
project(project VERSION 1.0)

##
## Extra packages: catch2
##
find_package(PkgConfig REQUIRED)
pkg_check_modules(CATCH2 REQUIRED catch2-with-main)

##
## Executable for test cases
##

add_executable(test_cases infectious.cpp infectious.hpp)

target_include_directories(
    test_cases PUBLIC ${CATCH2_INCLUDE_DIRS}
)

target_link_directories(
    test_cases PUBLIC ${CATCH2_LIBRARY_DIRS}
)

target_link_libraries(
    test_cases PUBLIC ${CATCH2_LIBRARIES}
)

set_target_properties(
    test_cases PROPERTIES
    BUILD_RPATH "${CATCH2_LIBRARY_DIRS}"
    INSTALL_RPATH "${CATCH2_LIBRARY_DIRS}"
)

target_compile_features(test_cases PRIVATE cxx_std_17)
install(TARGETS test_cases DESTINATION .)

##
## Executable for simulation without mutation
##

add_executable(finalproject infectious.cpp infectious.hpp main.cpp)

target_include_directories(
    finalproject PUBLIC ${CATCH2_INCLUDE_DIRS}
)

target_link_directories(
    finalproject PUBLIC ${CATCH2_LIBRARY_DIRS}
)

target_link_libraries(
    finalproject PUBLIC ${CATCH2_LIBRARIES}
)

set_target_properties(
    finalproject PROPERTIES
    BUILD_RPATH "${CATCH2_LIBRARY_DIRS}"
    INSTALL_RPATH "${CATCH2_LIBRARY_DIRS}"
)

target_compile_features(finalproject PRIVATE cxx_std_17)
install(TARGETS finalproject DESTINATION .)

##
## Executable for simulation with mutation
##

add_executable(finalproject_with_mutation infectious.cpp infectious_with_mutation.hpp infectious.hpp main2.cpp)

target_include_directories(
    finalproject_with_mutation PUBLIC ${CATCH2_INCLUDE_DIRS}
)

target_link_directories(
    finalproject_with_mutation PUBLIC ${CATCH2_LIBRARY_DIRS}
)

target_link_libraries(
    finalproject_with_mutation PUBLIC ${CATCH2_LIBRARIES}
)

set_target_properties(
    finalproject_with_mutation PROPERTIES
    BUILD_RPATH "${CATCH2_LIBRARY_DIRS}"
    INSTALL_RPATH "${CATCH2_LIBRARY_DIRS}"
)

target_compile_features(finalproject_with_mutation PRIVATE cxx_std_17)
install(TARGETS finalproject_with_mutation DESTINATION .)
