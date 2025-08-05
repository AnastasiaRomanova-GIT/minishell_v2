NAME =libft.a

CC = cc
PATH_C = ./
PATH_H = ./

FUNCTIONS = \
ft_isspace \
ft_isdigit \
ft_isquote \
ft_ismeta \
ft_memset \
ft_free_ptr_array \
ft_strlen \
ft_split \
ft_strdup \
ft_strcmp \
ft_strjoin \
ft_strncmp \
ft_strtrim \
ft_atoi \
ft_strnstr \
ft_isalnum \
ft_itoa\
ft_strrchr \
ft_strdigit \
ft_memcpy 
# ft_split_token \

SOURCES = $(addprefix $(PATH_C), $(addsuffix .c, $(FUNCTIONS)))

OBJECTS = $(SOURCES:.c=.o)
CCFLAGS = -Wall -Wextra -Werror

$(NAME): $(OBJECTS)
	ar rc $@ $^

all: $(NAME)

%.o: %.c
	@$(CC) $(CCFLAGS) -g -c -I$(PATH_H) $< -o $@

clean:
	rm -f $(OBJECTS) $(B_OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.SILENT: all clean fclean re
.PHONY: all clean fclean re