#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sperkhun <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/28 17:40:56 by sperkhun          #+#    #+#              #
#    Updated: 2018/02/28 17:40:57 by sperkhun         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = wolf3d

FLAGS = -Wall -Wextra -Werror

SRC = main.c draw.c ft_mlx.c thr.c readmap.c ray_cast.c move.c hook.c help.c

OBJ = $(SRC:.c=.o)

LIBFT = -L ./libft/ -lft

LIBML = -F ~/Library/Frameworks/ -framework SDL2 -framework SDL2_mixer\
	-L /usr/local/lib/ -lmlx  -framework OpenGL -framework AppKit

INCL = -I ./libft/includes/ -I ~/Library/Frameworks/SDL2.framework/Versions/A/Headers\
-I ~/Library/Frameworks/SDL2_mixer.framework/Versions/A/Headers -I /usr/local/include

all: $(NAME)

$(NAME): $(OBJ)
	@make -C ./libft/
	@gcc $(FLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(LIBML)
	@echo Creating wolf3d

%.o: %.c
	@gcc $(FLAGS) -c $< -o $@ $(INCL) -pthread

clean:
	@/bin/rm -f $(OBJ)
	@make -C ./libft/ clean

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C ./libft/ fclean
re: fclean all