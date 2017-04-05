# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: liton <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/09 15:35:38 by liton             #+#    #+#              #
#*   Updated: 2017/04/04 20:06:57 by liton            ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

CC = gcc

NAME = minishell

NAME_H = minishell.a

CFLAGS = -Wall -Wextra -Werror

SRC_NAME = main.c 

OBJ_DIR = obj

OBJ = $(SRC_NAME:.c=.o)

all:
#		@echo "Convesion des sources en objet"
		$(CC) $(CFLAGS) -c $(SRC_NAME)
#		@echo "Links des objets"
		ar rc $(NAME_H) $(OBJ)
#		@echo "Indexation de la librairie"
		ranlib $(NAME_H)
		$(CC) $(CFLAGS) $(SRC_NAME) libft.a -o $(NAME)
#		@echo "Creation du dossier objet"
		mkdir -p $(OBJ_DIR)
#		@echo "Les objets sont deplace dans le dossier objet"
		mv $(OBJ) $(OBJ_DIR)

clean:
#		@echo "Supression des objets"
		rm -f $(OBJ)
		rm -rf $(OBJ_DIR)

fclean: clean
#		@echo "Supression de l'executable et de la librairie"
		rm -f $(NAME)
		rm -f $(NAME_H)

re: fclean all

.PHONY: clean fclean re
