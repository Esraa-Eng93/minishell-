# === Compiler and Flags ===
NAME        = minishell
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g

# === Libraries ===
LIBFT_DIR   = ./libft
LIBFT       = $(LIBFT_DIR)/libft.a

# === Sources and Objects ===
SRC = main.c \
      srcs/tree_analyzing/tree_analyzing.c \
      srcs/tree_analyzing/analyzing_line1.c \
      srcs/tree_analyzing/analyzing_line2.c \
      srcs/tree_analyzing/analyzing_helping_codes.c \
      srcs/initalization/init.c \
      srcs/tree_analyzing/memory_free.c \
      srcs/tree_analyzing/export_helping_code.c \
      srcs/built_in/builtin_utilis2.c \
      srcs/built_in/echo_builtin.c \
      srcs/built_in/builtin_utilis.c \
      srcs/built_in/builtin_utilis3.c \
      srcs/built_in/env_builtin.c \
      srcs/tree_analyzing/handle_redirection.c \
      srcs/built_in/export_builtin.c \
      srcs/built_in/export_builtin2.c \
      srcs/built_in/cd_builtin.c \
      srcs/built_in/unset_builtin.c \
      srcs/built_in/pwd_builtin.c \
      srcs/built_in/exit_builtin.c \
      srcs/built_in/expand.c \
      srcs/signal/signal.c \
      srcs/minishell_execuation/minishell_exec1.c \
      srcs/minishell_execuation/minishell_exec2.c \
      srcs/minishell_execuation/minishell_exec3.c \
      srcs/minishell_execuation/minishell_execuation_utilis.c \
      srcs/minishell_execuation/execute.utilis.c \
      srcs/redirection/redirection_in.c \
      srcs/redirection/redirection_out.c \
      srcs/redirection/append_redirection.c \
      srcs/redirection/heredoc.c \
	srcs/pipes/pipes.c \
      srcs/pipes/pipe_utilis.c \
      srcs/pipes/pipe_execute.c \
      srcs/redirection/execuation.c \
      srcs/redirection/open_files.c \
      srcs/redirection/heredoc_expand.c \
      srcs/redirection/heredoc_expand2.c \
      srcs/redirection/open_heredoc.c \
      srcs/redirection/open_heredoc2.c \
      srcs/redirection/open_heredoc3.c \
      srcs/tree_analyzing/syntax_logic.c \
       srcs/tree_analyzing/analyzing_line3.c\
		srcs/tree_analyzing/analyzing_line4.c\
		srcs/tree_analyzing/analyzing_line5.c\
		srcs/tree_analyzing/handle_redirection2.c\
		srcs/tree_analyzing/handle_redirection3.c\
		srcs/tree_analyzing/syntax_redirection.c\

OBJ = $(SRC:.c=.o)

# === Build Rules ===

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	make -C $(LIBFT_DIR) --no-print-directory
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft -L$(GETLINE_DIR) -lgetline -lreadline -o $(NAME)

# === Commands ===

all: $(NAME)

clean:
	rm -f $(OBJ)
	make -C $(LIBFT_DIR) clean --no-print-directory

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean --no-print-directory

re: fclean all

.PHONY: all clean fclean re
