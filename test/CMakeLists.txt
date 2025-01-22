# Add GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

# Add the test executable
add_executable(
  ${PROJECT_NAME}_test
  test_main.cpp
  test_core_functionality.cpp
  test_huffman.cpp
  )
target_link_libraries(
  ${PROJECT_NAME}_test
  PUBLIC
  GTest::gtest_main
  PRIVATE
  ${PROJECT_NAME}_lib
  )

file(COPY ${CMAKE_SOURCE_DIR}/test/data/test.txt DESTINATION ${CMAKE_BINARY_DIR}/test/data)

# Add the tests
enable_testing()
add_test(
  NAME ${PROJECT_NAME}_test
  COMMAND ${PROJECT_NAME}_test
  )
