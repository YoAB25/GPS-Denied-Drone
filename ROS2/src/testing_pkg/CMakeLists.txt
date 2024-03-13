cmake_minimum_required(VERSION 3.8)
project(testing_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)

# adding executable and targets
add_executable(nodeA src/publisher_nodeA.cpp)
ament_target_dependencies(nodeA rclcpp std_msgs)

add_executable(nodeB src/pubsub_nodeB.cpp)
ament_target_dependencies(nodeB rclcpp std_msgs)

add_executable(nodeC src/subscriber_nodeC.cpp)
ament_target_dependencies(nodeC rclcpp std_msgs)

install(TARGETS
  nodeA
  nodeB
  nodeC
  DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
