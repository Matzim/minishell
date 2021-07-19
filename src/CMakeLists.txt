add_subdirectory(libft)
add_subdirectory(history)
add_subdirectory(execution)

add_executable(minishell minishell.c)

# Add compiles flags
target_link_libraries(minishell
    ${CURSES_LIBRARIES}
    libft
    history
    execution
)
