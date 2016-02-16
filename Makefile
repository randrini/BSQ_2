#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: randrini <randrini@student.42.fr>          +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2016/02/05 20:14:49 by randrini          #+#    #+#             *#
#*   Updated: 2016/02/16 18:58:18 by randrini         ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

NAME = bsq

SRC = $(wildcard srcs/*.c)

FLAG = -Wall -Werror -Wextra

OBJ = *.o

all: $(NAME)

$(NAME):
	@gcc $(FLAG) $(SRC) -c
	@gcc $(FLAG) $(SRC) -o $(NAME)

clean:
	@/bin/rm -rf $(OBJ)

fclean: clean
	@/bin/rm -rf $(NAME)
	@/bin/rm -rf stdin_grid

re: fclean all
