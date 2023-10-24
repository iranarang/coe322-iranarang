cmake_minimum_required( VERSION 3.12 )
project( hw9 VERSION 1.0 )

add_executable( hw9 linkedlist.cpp linkedlist.hpp )
target_compile_features( hw9 PRIVATE cxx_std_17 )
install( TARGETS hw9 DESTINATION . )