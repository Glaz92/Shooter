#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Box2D" for configuration "Release"
set_property(TARGET Box2D APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Box2D PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/libBox2D.dll.a"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/libBox2D.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS Box2D )
list(APPEND _IMPORT_CHECK_FILES_FOR_Box2D "${_IMPORT_PREFIX}/lib/libBox2D.dll.a" "${_IMPORT_PREFIX}/bin/libBox2D.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
