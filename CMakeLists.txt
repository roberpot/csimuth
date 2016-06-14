#
# Copyright 2016 Roberto García Carvajal
#
# This file is part of CSimuth.
# CSimuth is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# CSimuth is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with CSimuth. If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 2.8)
project(csimuth)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ansi -Wall -Wextra -pipe -pedantic -O3 -std=c++11")

set(SOURCE_FILES
        include/csimuth.h
        include/defines.h
        include/mutex.h src/mutex.cpp
        include/cond.h src/cond.cpp
        include/thread.h src/thread.cpp)

add_library(csimuth SHARED ${SOURCE_FILES})
add_library(csimuthstatic STATIC ${SOURCE_FILES})

set_target_properties(csimuthstatic PROPERTIES OUTPUT_NAME csimuth)

install(TARGETS csimuth csimuthstatic DESTINATION lib)
install(DIRECTORY "${PROJECT_SOURCE_DIR}/include/" DESTINATION include/csimuth)

# uninstall target
configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
        IMMEDIATE @ONLY)

add_custom_target(uninstall
        COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
