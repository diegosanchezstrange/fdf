NAME	= fdf

CC		= gcc

CFLAGS	= -Wall -Werror -Wextra -D BUFFER_SIZE=32 -g3 -fsanitize=address

SRCS	= fdf.c hooks.c line.c parse.c frees.c parse_utils.c

OBJS	= ${SRCS:.c=.o}

SRCS_DIR = src
OBJS_DIR = obj

LIBFT_NAME	= libft.a

MLX_NAME_MAC = libmlx.a
MLX_NAME_LINUX = libmlx_Linux.a

LIBFT	= lib/libft/
MLX	= lib/minilibx_macos/

SRCS_PATHS 	= $(addprefix $(SRCS_DIR)/, $(SRCS))

OBJS_PATHS 	= $(addprefix $(OBJS_DIR)/, $(OBJS))

RM		= rm -rf

MLX_LNK	= -L ${MLX} -l mlx -framework OpenGL -framework AppKit

LIB_LNK	= -L ${LIBFT} -lft

INCLUDES = -I${LIBFT}inc -I${MLX} -I ./inc

all: ${NAME}

${OBJS_DIR}/%.o: ${SRCS_DIR}/%.c
	@${CC} ${CFLAGS} -c $< -o $@ ${INCLUDES}

$(NAME): ${OBJS_DIR} ${OBJS_PATHS} 
	make -C ${LIBFT}
	make -C ${MLX}
	${CC} ${CFLAGS} ${LIB_LNK} ${MLX_LNK} ${OBJS_PATHS} -o ${NAME}

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR) 2> /dev/null

clean:
		@${RM} ${OBJS} *.dSYM

fclean:		clean
		@${RM} ${NAME}

bonus: all

re:		fclean all

.PHONY:	clean re fclean bonus all
