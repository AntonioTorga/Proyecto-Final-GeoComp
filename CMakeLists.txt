cmake_minimum_required(VERSION 3.15)
if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()

project(TriangleToQuadConverter)

find_package(CGAL REQUIRED)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/src/OFFManager.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/TriangleToQuadConverter.cpp
)

set(HEADERS
	${CMAKE_CURRENT_SOURCE_DIR}/include/TriangleToQuadConverter/OFFManager.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/TriangleToQuadConverter/TriangleToQuadConverter.h
)

if(FALSE)
add_subdirectory(extern)
add_subdirectory(test)

enable_testing()
endif()

add_library(TriangleToQuadConverter STATIC ${SOURCES} ${HEADERS})
target_include_directories(TriangleToQuadConverter PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/TriangleToQuadConverter)

add_executable(main ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

target_link_libraries(TriangleToQuadConverter PUBLIC CGAL::CGAL)
target_link_libraries(main PUBLIC TriangleToQuadConverter CGAL::CGAL)