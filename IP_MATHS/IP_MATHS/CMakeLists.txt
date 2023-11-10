# CMakeList.txt : CMake project for IP_MATHS, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (IP_MATHS "IP_MATHS.cpp" "IP_MATHS.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET IP_MATHS PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
