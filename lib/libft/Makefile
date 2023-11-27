# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yiwong <yiwong@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/12 14:24:09 by yiwong            #+#    #+#              #
#    Updated: 2022/12/17 22:27:56 by yiwong           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

AR = ar rcs

DEPS = libft.h

SRC =	ft_atoi.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_itoa.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_split.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strmapi.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strtrim.c \
		ft_substr.c \
		ft_tolower.c \
		ft_toupper.c


OBJ = $(SRC:.c=.o)

BONUS_SRC = ft_lstadd_back.c \
			ft_lstadd_front.c \
			ft_lstclear.c \
			ft_lstdelone.c \
			ft_lstiter.c \
			ft_lstlast.c \
			ft_lstmap.c \
			ft_lstnew.c \
			ft_lstsize.c

BONUS_OBJ = $(BONUS_SRC:.c=.o)

NAME = libft.a

all : $(NAME)

$(NAME) : $(OBJ)
		@$(CC) $(CFLAGS) -c $(SRC)
		@$(AR) $(NAME) $(OBJ)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

bonus : $(OBJ) $(BONUS_OBJ)
		@$(CC) $(CFLAGS) -c $(SRC) $(BONUS_SRC)
		@$(AR) $(NAME) $(OBJ) $(BONUS_OBJ)

clean :
		 @rm -f $(OBJ) $(BONUS_OBJ)

fclean : clean
		 @rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re bonus
