cmake_minimum_required( VERSION 3.12 )
project( hw6 VERSION 1.0 )

add_executable( hw6 newton-lambda.cpp )
target_compile_features( hw6 PRIVATE cxx_std_17 )

##
## Extra package: cxxopts
##
find_package( PkgConfig REQUIRED )
pkg_check_modules( OPTS REQUIRED cxxopts )
target_include_directories(
    hw6 PUBLIC
        ${OPTS_INCLUDE_DIRS}
        )

install( TARGETS hw6 DESTINATION . )