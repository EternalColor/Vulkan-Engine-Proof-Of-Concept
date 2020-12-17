add_executable(${PROJECT_NAME} ${SRC})

#Vulkan
target_link_libraries(${PROJECT_NAME} PRIVATE vulkan)
#GLFW3 and dependencies
target_link_libraries(${PROJECT_NAME} PRIVATE dl)
target_link_libraries(${PROJECT_NAME} PRIVATE pthread)
target_link_libraries(${PROJECT_NAME} PRIVATE X11)
target_link_libraries(${PROJECT_NAME} PRIVATE Xxf86vm)
target_link_libraries(${PROJECT_NAME} PRIVATE Xrandr)
target_link_libraries(${PROJECT_NAME} PRIVATE Xi)
target_link_libraries(${PROJECT_NAME} PRIVATE Xinerama)
target_link_libraries(${PROJECT_NAME} PRIVATE Xcursor)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
#GLM
target_link_libraries(${PROJECT_NAME} PRIVATE glm)