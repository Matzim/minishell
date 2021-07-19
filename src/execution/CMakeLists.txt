add_library(execution STATIC
    builtins.h
    builtins.c
    get_environ.h
    get_environ.c
    manage_input.h
    manage_input.c
    shell_management.h
    shell_management.c
    process.h
    process.c
)

# Add compiles flags
target_link_libraries(execution PRIVATE
    libft
    history
)
