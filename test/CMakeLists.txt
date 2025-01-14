include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

enable_testing()

message(STATUS "Adding ${PROJECT_NAME}_test")
add_executable(
  ${PROJECT_NAME}_test
  test_main.cpp
  )

target_link_libraries(
  compress0r_test
  GTest::gtest_main
  )

include(GoogleTest)
gtest_discover_tests(compress0r_test)

FetchContent_MakeAvailable(googletest)
