NAME	= fdf

CC		= gcc

CFLAGS	= -Wall -Werror -Wextra -D BUFFER_SIZE=32 -g3 -fsanitize=address

SRCS	= fdf.c

LIBFT_NAME	= libft.a

MLX_NAME_MAC = libmlx.a
MLX_NAME_LINUX = libmlx_Linux.a

LIBFT	= lib/libft/
MLX	= lib/minilibx_macos/

OBJS	= ${SRCS:.c=.o}

RM		= rm -rf

MLX_LNK	= -L ${MLX} -l mlx -framework OpenGL -framework AppKit

INCLUDES = -I${LIBFT}inc -I${MLX} -I ./inc

all: ${NAME}

.c.o:
	${CC} ${CFLAGS} -c ${INCLUDES} $< -o ${<:.c=.o}

$(NAME): ${OBJS}
	${CC} ${CFLAGS} ${MLX_LNK} ${OBJS} -o ${NAME}

clean:
		@${RM} ${OBJS} *.dSYM

fclean:		clean
		@${RM} ${NAME}

bonus: all

re:		fclean all

.PHONY:	clean re fclean bonus all
