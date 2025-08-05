# name of the project
NAME = minishell
# compiler and flags for the compilation
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
DBGLAGS = -Wall -Wextra -Werror -g -fsanitize=address,leak,thread,undefined
DBPRINT = -Wall -Wextra -Werror -DDEBUG_MODE=1
# -Wall -Wextra -Werror
# -fsanitize=undefined
# -fsanitize=thread
# -fsanitize=memory
# -fsanitize=leak

#which libft do we use? Do we compile all of it?`
LIB_FOLDER = ./libft
LIB_NAME = libft.a 

HELPERS = \
utils/exit_utils.c \
utils/debug_utils.c \
token_processing/token_util.c \
token_processing/parse_redirection.c \
token_processing/heredoc_processing.c \
token_processing/init_token.c \
token_processing/parse.c \
token_processing/tokenise.c \
execute/exec_manager.c \
execute/executors.c \
execute/pipe_exec.c \
execute/echo_trial.c \
signals/signal_handlers.c \
input/env_copy.c \
builtin/builtin.c\
builtin/echo.c \
builtin/echo_util.c \
builtin/export.c\
builtin/exit.c\
error_check.c \


all:
	$(MAKE) -C $(LIB_FOLDER) all
	$(CC) $(CFLAGS) $(NAME).c $(HELPERS) $(LIB_FOLDER)/$(LIB_NAME) -lreadline -lncurses -o $(NAME)

exec_only:
	rm -f $(NAME)
	$(CC) $(CFLAGS) $(NAME).c $(HELPERS) $(LIB_FOLDER)/$(LIB_NAME) -lreadline -lncurses -o $(NAME)

debug:
	rm -f $(NAME)
	$(CC) $(DBGLAGS) $(NAME).c $(HELPERS) $(LIB_FOLDER)/$(LIB_NAME) -lreadline -lncurses -o $(NAME)

print_debug:
	rm -f $(NAME)
	$(CC) $(DBPRINT) $(NAME).c $(HELPERS) $(LIB_FOLDER)/$(LIB_NAME) -lreadline -lncurses -o $(NAME)

clean:
	rm -f $(NAME)

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIB_FOLDER) fclean

re: fclean all

.PHONY: all clean fclean re
