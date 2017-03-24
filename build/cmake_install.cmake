# Install script for directory: D:/OpenIGTLink/OpenIGTLink

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/OpenIGTLink")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/igtl/cmake/igtl-3.0" TYPE FILE FILES
    "D:/OpenIGTLink/OpenIGTLink/build/OpenIGTLinkBuildSettings.cmake"
    "D:/OpenIGTLink/OpenIGTLink/build/UseOpenIGTLink.cmake"
    "D:/OpenIGTLink/OpenIGTLink/build/Utilities/OpenIGTLinkConfig.cmake"
    )
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/igtl" TYPE FILE FILES "D:/OpenIGTLink/OpenIGTLink/build/igtlConfigure.h")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/igtl" TYPE FILE FILES "D:/OpenIGTLink/OpenIGTLink/build/igtl_typeconfig.h")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/igtl" TYPE FILE FILES "D:/OpenIGTLink/OpenIGTLink/build/igtlTypeConfig.h")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/igtl/cmake/igtl-3.0/OpenIGTLinkTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/igtl/cmake/igtl-3.0/OpenIGTLinkTargets.cmake"
         "D:/OpenIGTLink/OpenIGTLink/build/CMakeFiles/Export/lib/igtl/cmake/igtl-3.0/OpenIGTLinkTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/igtl/cmake/igtl-3.0/OpenIGTLinkTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/igtl/cmake/igtl-3.0/OpenIGTLinkTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/igtl/cmake/igtl-3.0" TYPE FILE FILES "D:/OpenIGTLink/OpenIGTLink/build/CMakeFiles/Export/lib/igtl/cmake/igtl-3.0/OpenIGTLinkTargets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/igtl/cmake/igtl-3.0" TYPE FILE FILES "D:/OpenIGTLink/OpenIGTLink/build/CMakeFiles/Export/lib/igtl/cmake/igtl-3.0/OpenIGTLinkTargets-debug.cmake")
  endif()
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/igtl/cmake/igtl-3.0" TYPE FILE FILES "D:/OpenIGTLink/OpenIGTLink/build/CMakeFiles/Export/lib/igtl/cmake/igtl-3.0/OpenIGTLinkTargets-minsizerel.cmake")
  endif()
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/igtl/cmake/igtl-3.0" TYPE FILE FILES "D:/OpenIGTLink/OpenIGTLink/build/CMakeFiles/Export/lib/igtl/cmake/igtl-3.0/OpenIGTLinkTargets-relwithdebinfo.cmake")
  endif()
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/igtl/cmake/igtl-3.0" TYPE FILE FILES "D:/OpenIGTLink/OpenIGTLink/build/CMakeFiles/Export/lib/igtl/cmake/igtl-3.0/OpenIGTLinkTargets-release.cmake")
  endif()
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("D:/OpenIGTLink/OpenIGTLink/build/Source/cmake_install.cmake")
  include("D:/OpenIGTLink/OpenIGTLink/build/Tools/cmake_install.cmake")
  include("D:/OpenIGTLink/OpenIGTLink/build/Testing/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "D:/OpenIGTLink/OpenIGTLink/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
