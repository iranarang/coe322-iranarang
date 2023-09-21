cmake_minimum_required( VERSION 3.12 )
project( hw5 VERSION 1.0 )

add_executable( hw5 goldbach.cpp )
install( TARGETS hw5 DESTINATION . )
