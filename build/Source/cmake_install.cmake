# Install script for directory: D:/OpenIGTLink/OpenIGTLink/Source

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/igtl" TYPE FILE FILES
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlutil/igtl_header.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlutil/igtl_image.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlutil/igtl_position.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlutil/igtl_transform.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlutil/igtl_types.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlutil/igtl_util.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlutil/igtl_capability.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlutil/igtl_win32header.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlMessageHandler.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlMessageHandlerMacro.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlCapabilityMessage.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlClientSocket.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlConditionVariable.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlCreateObjectFunction.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlFastMutexLock.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlImageMessage.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlImageMessage2.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlLightObject.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlMacro.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlMath.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlMessageBase.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlMessageFactory.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlMessageHeader.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlMultiThreader.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlMutexLock.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlObjectFactory.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlOSUtil.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlObject.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlObjectFactoryBase.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlPositionMessage.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlServerSocket.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlSessionManager.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlSimpleFastMutexLock.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlSmartPointer.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlSocket.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlStatusMessage.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlTimeStamp.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlTransformMessage.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlTypes.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlWin32Header.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlWindows.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlCommon.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlutil/igtl_colortable.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlutil/igtl_imgmeta.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlutil/igtl_lbmeta.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlutil/igtl_point.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlutil/igtl_tdata.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlutil/igtl_qtdata.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlutil/igtl_trajectory.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlutil/igtl_unit.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlutil/igtl_sensor.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlutil/igtl_string.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlutil/igtl_ndarray.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlutil/igtl_bind.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlutil/igtl_qtrans.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlutil/igtl_polydata.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlColorTableMessage.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlImageMetaMessage.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlLabelMetaMessage.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlPointMessage.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlTrackingDataMessage.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlPolyDataMessage.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlQuaternionTrackingDataMessage.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlTrajectoryMessage.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlStringMessage.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlUnit.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlSensorMessage.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlBindMessage.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlNDArrayMessage.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlCommandMessage.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlQueryMessage.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlutil/igtl_command.h"
    "D:/OpenIGTLink/OpenIGTLink/Source/igtlutil/igtl_query.h"
    )
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/igtl" TYPE STATIC_LIBRARY FILES "D:/OpenIGTLink/OpenIGTLink/build/bin/Debug/OpenIGTLink.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/igtl" TYPE STATIC_LIBRARY FILES "D:/OpenIGTLink/OpenIGTLink/build/bin/Release/OpenIGTLink.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/igtl" TYPE STATIC_LIBRARY FILES "D:/OpenIGTLink/OpenIGTLink/build/bin/MinSizeRel/OpenIGTLink.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/igtl" TYPE STATIC_LIBRARY FILES "D:/OpenIGTLink/OpenIGTLink/build/bin/RelWithDebInfo/OpenIGTLink.lib")
  endif()
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("D:/OpenIGTLink/OpenIGTLink/build/Source/igtlutil/cmake_install.cmake")

endif()

