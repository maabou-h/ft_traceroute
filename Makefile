# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maabou-h <maabou-h@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/13 18:42:02 by maabou-h          #+#    #+#              #
#    Updated: 2019/08/16 15:04:04 by maabou-h         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := ft_traceroute
CC ?= clang
CFLAGS ?= -Werror -Wall -Wextra

SRC := srcs/checker.c\
		   srcs/checksum.c\
		   srcs/ft_traceroute.c\
		   srcs/helper.c\
		   srcs/init.c\
		   srcs/options.c\
		   srcs/packer.c\
		   srcs/unpacker.c



HDR := incs/

OBJ := $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) -I$(HDR)
	
%.o: %.c $(HDR)ft_ping.h Makefile
	$(CC) $(CFLAGS) -o $@ -c $< -I$(HDR)

clean:
	rm -rfv $(OBJ)

fclean: clean
	rm -fv $(NAME)

re: fclean all

.PHONY: all clean fclean re
