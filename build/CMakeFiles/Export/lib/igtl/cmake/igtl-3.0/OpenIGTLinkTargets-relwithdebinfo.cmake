#----------------------------------------------------------------
# Generated CMake target import file for configuration "RelWithDebInfo".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "OpenIGTLink" for configuration "RelWithDebInfo"
set_property(TARGET OpenIGTLink APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(OpenIGTLink PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELWITHDEBINFO "C;CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELWITHDEBINFO "ws2_32;wsock32"
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/igtl/OpenIGTLink.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS OpenIGTLink )
list(APPEND _IMPORT_CHECK_FILES_FOR_OpenIGTLink "${_IMPORT_PREFIX}/lib/igtl/OpenIGTLink.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
