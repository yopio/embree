include(FindPackageHandleStandardArgs)

find_path(GLM_INCLUDE_DIR NAMES glm/glm.hpp PATHS
  /usr/include
  /usr/local/include
  /opt/local/include)

find_package_handle_standard_args(GLM DEFAULT_MSG GLM_INCLUDE_DIR)

if(GLM_FOUND)
  set(GLM_INCLUDE_DIRS ${GLM_INCLUDE_DIR})
endif()

# hide some variables
mark_as_advanced(GLM_INCLUDE_DIR)
