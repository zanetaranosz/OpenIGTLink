# Generated by CMake

if("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" LESS 2.5)
   message(FATAL_ERROR "CMake >= 2.6.0 required")
endif()
cmake_policy(PUSH)
cmake_policy(VERSION 2.6)
#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Protect against multiple inclusion, which would fail when already imported targets are added once more.
set(_targetsDefined)
set(_targetsNotDefined)
set(_expectedTargets)
foreach(_expectedTarget OpenIGTLink)
  list(APPEND _expectedTargets ${_expectedTarget})
  if(NOT TARGET ${_expectedTarget})
    list(APPEND _targetsNotDefined ${_expectedTarget})
  endif()
  if(TARGET ${_expectedTarget})
    list(APPEND _targetsDefined ${_expectedTarget})
  endif()
endforeach()
if("${_targetsDefined}" STREQUAL "${_expectedTargets}")
  unset(_targetsDefined)
  unset(_targetsNotDefined)
  unset(_expectedTargets)
  set(CMAKE_IMPORT_FILE_VERSION)
  cmake_policy(POP)
  return()
endif()
if(NOT "${_targetsDefined}" STREQUAL "")
  message(FATAL_ERROR "Some (but not all) targets in this export set were already defined.\nTargets Defined: ${_targetsDefined}\nTargets not yet defined: ${_targetsNotDefined}\n")
endif()
unset(_targetsDefined)
unset(_targetsNotDefined)
unset(_expectedTargets)


# Create imported target OpenIGTLink
add_library(OpenIGTLink STATIC IMPORTED)

set_target_properties(OpenIGTLink PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "D:/OpenIGTLink/OpenIGTLink/build;D:/OpenIGTLink/OpenIGTLink/Source;D:/OpenIGTLink/OpenIGTLink/build/Source;D:/OpenIGTLink/OpenIGTLink/Source/igtlutil;D:/OpenIGTLink/OpenIGTLink/build/Source/igtlutil"
)

# Import target "OpenIGTLink" for configuration "Debug"
set_property(TARGET OpenIGTLink APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(OpenIGTLink PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C;CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "ws2_32;wsock32"
  IMPORTED_LOCATION_DEBUG "D:/OpenIGTLink/OpenIGTLink/build/bin/Debug/OpenIGTLink.lib"
  )

# Import target "OpenIGTLink" for configuration "Release"
set_property(TARGET OpenIGTLink APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(OpenIGTLink PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C;CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "ws2_32;wsock32"
  IMPORTED_LOCATION_RELEASE "D:/OpenIGTLink/OpenIGTLink/build/bin/Release/OpenIGTLink.lib"
  )

# Import target "OpenIGTLink" for configuration "MinSizeRel"
set_property(TARGET OpenIGTLink APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(OpenIGTLink PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_MINSIZEREL "C;CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_MINSIZEREL "ws2_32;wsock32"
  IMPORTED_LOCATION_MINSIZEREL "D:/OpenIGTLink/OpenIGTLink/build/bin/MinSizeRel/OpenIGTLink.lib"
  )

# Import target "OpenIGTLink" for configuration "RelWithDebInfo"
set_property(TARGET OpenIGTLink APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(OpenIGTLink PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELWITHDEBINFO "C;CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELWITHDEBINFO "ws2_32;wsock32"
  IMPORTED_LOCATION_RELWITHDEBINFO "D:/OpenIGTLink/OpenIGTLink/build/bin/RelWithDebInfo/OpenIGTLink.lib"
  )

# This file does not depend on other imported targets which have
# been exported from the same project but in a separate export set.

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
cmake_policy(POP)
