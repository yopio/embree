include(FindPackageHandleStandardArgs)

find_path(OPENIMAGEIO_INCLUDE_DIR NAMES OpenImageIO/imageio.h PATHS
  /usr/include
  /usr/local/include
  /opt/local/include)

find_path(OPENIMAGEIO_LIBRARY_PATH NAMES OpenImageIO PATHS
  /lib
  /usr/lib
  /usr/local/lib
  /opt/local/lib)

find_package_handle_standard_args(OPENIMAGEIO DEFAULT_MSG
  OPENIMAGEIO_INCLUDE_DIR
  OPENIMAGEIO_LIBRARY_PATH)

if(OPENIMAGEIO_FOUND)
  set(OPENIMAGEIO_INCLUDE_DIRS  ${OPENIMAGEIO_INCLUDE_DIR})
  set(OPENIMAGEIO_LIBRARY_PATHS ${OPENIMAGEIO_LIBRARY_PATHS})
endif()

# hide some variables
mark_as_advanced(OPENIMAGEIO_INCLUDE_DIR OPENIMAGEIO_LIBRARY_PATHS)
