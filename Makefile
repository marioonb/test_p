# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbelorge <mbelorge@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/10 13:40:03 by mbelorge          #+#    #+#              #
#    Updated: 2021/02/10 14:36:21 by mbelorge         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	main.c\
			utils.c \
			ft_error.c \
			action.c \
			init.c \
			monitor.c \
			free_all.c \

NAME	= philo

OBJS	= ${SRCS:.c=.o}

CFLAGS	=	-Wall -Wextra -Werror 

LOGFILE = $(LOGPATH) `date +'%y.%m.%d %H:%M:%S'`
MSG = auto save

%.o: %.c
		gcc $(CFLAGS) -o $@ -c $<

$(NAME):	${OBJS}
			gcc -g  -o $(NAME) $(OBJS)

all:		${NAME}

clean:
			rm -f ${OBJS}

fclean:		clean
			rm -f ${NAME}

git : fclean
	@(git add *)
	@(git commit -m "$(LOGFILE) : $(MSG)")
	@(git push)

re:			fclean all

.PHONY:		all clean fclean
