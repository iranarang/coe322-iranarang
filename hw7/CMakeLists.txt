cmake_minimum_required( VERSION 3.12 )
project( fmtbasic VERSION 1.0 )

message( "Using sources: align.cpp ${EXTRA_SOURCES}" )
add_executable( hw7 align.cpp ${EXTRA_SOURCES} )
target_compile_features( hw7 PRIVATE cxx_std_17 )

##
## Extra packages: fmtlib
##
find_package( PkgConfig REQUIRED )
pkg_check_modules( FMTLIB REQUIRED fmt )
message( "Include dirs:  ${FMTLIB_INCLUDE_DIRS}" )
message( "Lib dirs and libs:  ${FMTLIB_LIBRARY_DIRS} ${FMTLIB_LIBRARIES}" )
target_include_directories(
	hw7 PUBLIC ${FMTLIB_INCLUDE_DIRS}
	)
target_link_directories(
	hw7 PUBLIC ${FMTLIB_LIBRARY_DIRS}
	)
target_link_libraries(
	hw7 PUBLIC ${FMTLIB_LIBRARIES}
	)
set_target_properties(
	hw7 PROPERTIES
	BUILD_RPATH   "${FMTLIB_LIBRARY_DIRS}"
	INSTALL_RPATH "${FMTLIB_LIBRARY_DIRS}"
    )

install( TARGETS hw7 DESTINATION . )