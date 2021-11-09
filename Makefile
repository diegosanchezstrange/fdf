NAME	= pipex

CC		= gcc

CFLAGS	= -Wall -Werror -Wextra -D BUFFER_SIZE=32 -g3 -fsanitize=address

SRCS	= fdf.c

LIBFT_NAME	= libft.a

MLX_NAME_MAC = libmlx.a
MLX_NAME_LINUX = libmlx_Linux.a

LIBFT	= lib/libft/

OBJS	= ${SRCS:.c=.o}

RM		= rm -rf

MLX		= lib/${MLX_DIR}/

all: ${NAME}

.c.o:
	${CC} ${CFLAGS} -c -I${LIBFT}inc $< -o ${<:.c=.o}

$(NAME): ${OBJS}
	${CC} ${CFLAGS} ${INCLUDE} ${OBJS} -o ${NAME}

$()

clean:
		@${RM} ${OBJS} *.dSYM

fclean:		clean
		@${RM} ${NAME}

bonus: all

re:		fclean all

.PHONY:	clean re fclean bonus all
