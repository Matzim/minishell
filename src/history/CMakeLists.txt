add_library(history STATIC
    cursor.h
    cursor.c
    history.h
    history.c
    vector.h
    vector.c
)

# Add compiles flags
target_link_libraries(history PRIVATE
    libft
)
