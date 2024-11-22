cmake_minimum_required(VERSION 3.5.0)
project(VulkanTriangle VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)

add_executable(VulkanTriangle main.cpp)

include(cmake/CPM.cmake)

find_package(Vulkan)
target_link_libraries(VulkanTriangle Vulkan::Vulkan)

CPMAddPackage("gh:glfw/glfw#3.4")
target_link_libraries(VulkanTriangle glfw)

CPMAddPackage("gh:g-truc/glm#1.0.1")
target_link_libraries(VulkanTriangle glm)