add_library(libft
    ft_atoi.c
    ft_putstr.c
    ft_split_whitespace.c
    ft_strcmp.c
    ft_strdup.c
    ft_strjoin.c
    ft_strlen.c
)

set_target_properties(libft PROPERTIES PUBLIC_HEADER libft.h)

install(TARGETS libft
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  PUBLIC_HEADER DESTINATION include
)
