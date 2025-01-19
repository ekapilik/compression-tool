set(lib_srcs
  frequency.hpp
  frequency.cpp
  )

add_library(${PROJECT_NAME}_lib
  STATIC
  ${lib_srcs}
  )

# Make headers available to other targets that link to this library
target_include_directories(${PROJECT_NAME}_lib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/>  # During build
)
