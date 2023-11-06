cmake_minimum_required( VERSION 3.12 )
project( hw10 VERSION 1.0 )


##
## Extra packages: catch2
##
find_package( PkgConfig REQUIRED )
pkg_check_modules( CATCH2 REQUIRED catch2-with-main )

##
## main
##

add_executable( hw10 hw10.cpp hw10.hpp)

target_include_directories( 
	hw10 PUBLIC ${CATCH2_INCLUDE_DIRS}
	)

target_link_directories(
	hw10 PUBLIC	${CATCH2_LIBRARY_DIRS}
	)
target_link_libraries(
	hw10 PUBLIC ${CATCH2_LIBRARIES}
	)

set_target_properties(
	hw10 PROPERTIES
	BUILD_RPATH   "${CATCH2_LIBRARY_DIRS}"
	INSTALL_RPATH "${CATCH2_LIBRARY_DIRS}"
    )

target_compile_features( hw10 PRIVATE cxx_std_17 )
install( TARGETS hw10 DESTINATION . )