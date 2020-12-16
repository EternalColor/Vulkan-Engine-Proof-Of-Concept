add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} PUBLIC vulkan)
#Libraries that are needed by glfw3 inderictely
target_link_libraries(${PROJECT_NAME} PUBLIC dl)
target_link_libraries(${PROJECT_NAME} PUBLIC pthread)
target_link_libraries(${PROJECT_NAME} PUBLIC X11)
target_link_libraries(${PROJECT_NAME} PUBLIC Xxf86vm)
target_link_libraries(${PROJECT_NAME} PUBLIC Xrandr)
target_link_libraries(${PROJECT_NAME} PUBLIC Xi)
target_link_libraries(${PROJECT_NAME} PUBLIC Xinerama)
target_link_libraries(${PROJECT_NAME} PUBLIC Xcursor)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw3)