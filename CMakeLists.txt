cmake_minimum_required(VERSION 3.7 FATAL_ERROR)

foreach(p
        CMP0025 # CMake 3.0
        CMP0042 # CMake 3.0
        CMP0028 # CMake 3.0
        CMP0063 # honor visibility settings also for static libs
        CMP0057 # for doxygen
        CMP0074)
  if(POLICY ${p})
    cmake_policy(SET ${p} NEW)
  endif()
endforeach()

project(alo VERSION 1.0.0 LANGUAGES CXX C)

set(CMAKE_MODULE_PATH "${alo_SOURCE_DIR}/cmake")

find_package(ROOT)
find_package(AliRoot)
find_package(O2)
find_package(RapidJSON)
find_package(FlatBuffers)
find_package(yaml-cpp REQUIRED)

find_package(Boost 1.59
             COMPONENTS unit_test_framework
                        program_options
                        filesystem
                        serialization
                        REQUIRED)

include(CTest)

add_subdirectory(dataformats)
add_subdirectory(utilities)

if(AliRoot_FOUND)
  add_subdirectory(aliroot)
endif()

if(O2_FOUND)
  add_subdirectory(o2)
endif()

if(${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}.${CMAKE_PATCH_VERSION} GREATER
   3.9.6)
  # doxygen_add_docs command was added in CMake 3.9.6
  find_package(Doxygen OPTIONAL_COMPONENT dot)
  if(DOXYGEN_FOUND)
    set(DOXYGEN_JAVADOC_AUTOBRIEF YES)
    set(DOXYGEN_OPTIMIZE_OUTPUT_FOR_C YES)
    set(DOXYGEN_WARN_IF_UNDOCUMENTED NO)
    doxygen_add_docs(doc)
  endif()
endif()
