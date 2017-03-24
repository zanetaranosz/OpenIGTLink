PROJECT(Lab_PWP)

cmake_minimum_required(VERSION 2.4)
if(COMMAND cmake_policy)
  cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

find_package(OpenIGTLink REQUIRED)

include(${OpenIGTLink_USE_FILE})

ADD_EXECUTABLE(NowyClient   NowyClient.cxx)
TARGET_LINK_LIBRARIES(NowyClient OpenIGTLink)


ADD_EXECUTABLE(NowyServer  NowyServer.cxx)
TARGET_LINK_LIBRARIES(NowyServer OpenIGTLink)

