# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/03/15 17:31:08 by volivry      #+#   ##    ##    #+#        #
#    Updated: 2018/04/11 13:49:37 by volivry     ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY: all clean fclean re

CC = gcc
CCFLAGS = -Wall -Wextra -g
NAME = minishell
SRC =  main.c fork_ms.c
OBJECTS = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	@$(CC) $(CCFLAGS) -I. -o $@ -c $<

$(NAME): $(OBJECTS)
	@make -C ./libft/
	$(CC) $(CCFLAGS) -o $(NAME) $(OBJECTS) -L libft/ -lft

clean:
	@echo "CLEANING"
	@make clean -C ./libft/
	@rm -f $(OBJECTS)

fclean: clean
	@echo "SUPER CLEANING"
	@make fclean -C ./libft/
	@rm -f $(NAME)

re: fclean all
