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

SRCS_PATHS 	= $(addprefix $(SRCS_DIR)/, $(SRCS))

OBJS_PATHS 	= $(addprefix $(OBJS_DIR)/, $(OBJS))

RM		= rm -rf

OS		:= $(shell uname -s)

ifeq (${OS},Linux)
	MLX = lib/minilibx-linux/
	MLX_NAME = ${MLX_NAME_LINUX}
	LIBS = -lft -lmlx_Linux -lXext -lX11 -lm -lz
endif
ifeq (${OS},Darwin)
	MLX	= lib/minilibx_macos/
	MLX_NAME = ${MLX_NAME_MAC}
	LIBS = -lft -lmlx -framework OpenGL -framework AppKit
endif

MLX_LNK	= -L ${MLX}

LIB_LNK	= -L ${LIBFT}

INCLUDES = -I ./${LIBFT}inc -I ./${MLX} -I ./inc

all: ${NAME}

${OBJS_DIR}/%.o: ${SRCS_DIR}/%.c
	@${CC} ${CFLAGS} ${INCLUDES} -c $< -o $@ 

$(NAME): ${LIBFT_NAME} ${MLX_NAME} ${OBJS_DIR} ${OBJS_PATHS} 
	${CC} ${CFLAGS} ${LIB_LNK} ${MLX_LNK} ${OBJS_PATHS} -o ${NAME} ${LIBS}

${LIBFT_NAME} :
	make -C ${LIBFT}
	cp ${LIBFT}/${LIBFT_NAME} .

${MLX_NAME} :
	make -C ${MLX}
	cp ${MLX}/${MLX_NAME} .

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR) 2> /dev/null

clean:
		@${RM} ${OBJS} *.dSYM

fclean:		clean
		@${RM} ${NAME}

bonus: all

re:		fclean all

.PHONY:	clean re fclean bonus all
