# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/03/15 17:31:08 by volivry      #+#   ##    ##    #+#        #
#    Updated: 2018/05/08 11:23:47 by volivry     ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY: all clean fclean re

CC = gcc
CCFLAGS = -Wall -Wextra -Werror -g
NAME = minishell
SRCDIR = srcs
OBJDIR = objs
INCDIR = includes libft

SRC =  main.c fork_ms.c free_ms.c process.c get_args_ms.c builtin_ms.c \
	   utils_ms.c conv_str.c utils_conv_ms.c multi_cmd.c print_prompt.c \
	   cd_ms.c env_ms.c setenv_ms.c unsetenv_ms.c

SRCS = $(addprefix $(SRCDIR)/, $(SRC))
OBJECTS = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))
INCS = $(addprefix -I , $(INCDIR))

all: $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) $(CCFLAGS) -I. -o $@ -c $<

$(NAME): build $(OBJECTS)
	@make -C libft
	@$(CC) -L libft -lft -o $(NAME) $(OBJECTS)
	@(echo "\033[2K\033[2F")
	@(echo "\n\033[32m MiniShell compiled\033[0m";)

build:
	@mkdir -p $(OBJDIR)

clean:
	@echo "CLEANING OBJECTS"
	@make clean -C ./libft/
	@rm -f $(OBJECTS)

fclean: clean
	@echo "CLEANING ALL"
	@make fclean -C ./libft/
	@rm -f $(NAME)

re: fclean all
