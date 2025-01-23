SRC =	./src/main/main.c \
		./src/main/env_init.c \
		./src/main/free_all.c \
		./src/main/sig_init.c \
		./src/lexer/head_lexer/start_lexer.c \
		./src/lexer/head_lexer/syntax_ctrl.c \
		./src/lexer/head_lexer/metachar_split.c \
		./src/lexer/lexer_tools/lexer_utils.c \
		./src/lexer/lexer_tools/wspace_quotes_utils.c \
		./src/lexer/lexer_init_list/build_nodes.c \
		./src/lexer/lexer_init_list/lexer_init_tools.c \
		./src/lexer/lexer_init_list/assign_type.c \
		./src/expander/head_expander.c \
		./src/expander/expand_the_content.c \
		./src/expander/dollar_ctrl.c \
		./src/expander/dollar_tools.c \
		./src/expander/expander_init_tools.c \
		./src/parser/start_parser.c \
		./src/parser/init_hrdc.c \
		./src/parser/start_init.c \
		./src/parser/update_parser.c \
		./src/parser/fd_list_init.c \
		./src/parser/in_out_fd_init.c \
		./src/executer/exec/head_executer.c \
		./src/executer/exec/head_process.c \
		./src/executer/exec/duplicate.c \
		./src/executer/exec/r_command.c \
		./src/executer/builtin/ctrl_builtin.c \
		./src/executer/builtin/r_cd.c \
		./src/executer/builtin/r_echo.c \
		./src/executer/builtin/r_env.c \
		./src/executer/builtin/r_pwd.c \
		./src/executer/builtin/r_exit.c \
		./src/executer/builtin/r_export.c \
		./src/executer/builtin/r_unset.c \
		./src/executer/tools/env_exec_utils.c \
		./src/executer/tools/r_execve_utils.c \
		./src/executer/tools/env_arg_ctrl.c \
		./src/tools/print_errors.c \
		./src/tools/utilities.c \
		./src/tools/get_the_line.c \



NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g
RM = rm -rf
LIBFT = libft/libft.a
READLINE = readline

OBJ = $(SRC:.c=.o)

all : $(READLINE) $(LIBFT) $(NAME) 

$(READLINE):
	curl -O https://ftp.gnu.org/gnu/readline/readline-8.2.tar.gz
	tar -xvf readline-8.2.tar.gz
	cd readline-8.2 && ./configure --prefix=${PWD}/readline
	cd readline-8.2 && make install

$(LIBFT):
	@make -C libft
	@make bonus -C libft
	@make clean -C libft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${PWD}/readline/include/

$(NAME): $(SRC) $(LIBFT)
	@$(CC) $(CFLAGS) $(LIBFT) $(SRC) -L${PWD}/readline/lib  -I${PWD}/readline/include/ -lreadline -o $(NAME)
	@ make clean

clean:
	@$(RM) $(OBJ)


fclean: clean
	@$(RM) $(NAME)
	@make -C libft fclean
	@rm -rf readline-8.2 readline-8.2.tar.gz

re: fclean all

.PHONY: all clean fclean re