set(TASK_NAME __TASK_SLUG__)

add_executable(${TASK_NAME}_analytics analytics.cpp)

target_link_libraries(${TASK_NAME}_analytics PRIVATE
)

add_executable(${TASK_NAME}_simulation simulation.cpp)
