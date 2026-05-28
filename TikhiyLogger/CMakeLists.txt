# CMakeList.txt : CMake project for TikhiyLogger, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (TikhiyLogger "TikhiyLogger.cpp" "TikhiyLogger.h")
target_link_libraries(TikhiyLogger ntdll)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET TikhiyLogger PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
