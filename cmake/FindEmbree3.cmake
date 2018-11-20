include(FindPackageHandleStandardArgs)

find_path(EMBREE3_INCLUDE_DIR NAMES embree3/rtcore.h PATHS
  /usr/include
  /usr/local/include
  /opt/local/include)

find_path(EMBREE3_LIBRARY_PATH NAMES embree3 PATHS
  /lib
  /usr/lib
  /usr/local/lib
  /opt/local/lib)

find_package_handle_standard_args(EMBREE3 DEFAULT_MSG
  EMBREE3_INCLUDE_DIR
  EMBREE3_LIBRARY_PATH)

if(EMBREE3_FOUND)
  set(EMBREE3_INCLUDE_DIRS  ${EMBREE3_INCLUDE_DIR})
  set(EMBREE3_LIBRARY_PATHS ${EMBREE3_LIBRARY_PATH})
endif()

# hide some variables
mark_as_advanced(EMBREE3_INCLUDE_DIR EMBREE3_LIBRARY_PATH)
