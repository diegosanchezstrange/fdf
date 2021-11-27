/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 17:53:51 by dsanchez          #+#    #+#             */
/*   Updated: 2021/11/25 21:33:30 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <libft.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_point {
	int	x;
	int	y;
	int	z;
	int	color;
}				t_point;

typedef struct	s_fdf {
	void	*mlx;
	void	*win;
	t_point	**points;
	t_data	img;
	int		w;
	int		h;
	int		x_move;
	int		y_move;
	int		iso;
	int		par;
	int		proyec;
	int		scale;
	int		zoom;
	float		z;
}				t_fdf;

# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080

# define X_OFFSET 20
# define Y_OFFSET 20

# ifdef OSX
#  define KEY_ESC 53
#  define KEY_UP 126
#  define KEY_DOWN 125
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
#  define KEY_P 35
#  define KEY_MINUS 27
#  define KEY_PLUS 24
#  define KEY_C 69
# elif LINUX
#  define KEY_ESC 65307
#  define KEY_UP 65362
#  define KEY_DOWN 65364
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
#  define KEY_P 112
#  define KEY_PLUS 61
#  define KEY_C 99
# else
#  define LINUX
#  define KEY_ESC 65307
#  define KEY_UP 65362
#  define KEY_DOWN 65364
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
#  define KEY_P 112
#  define KEY_PLUS 61
#  define KEY_C 99
# endif

// free.c
void	ft_free_all(char **split, t_list **list, char *line);
void	ft_free_split(char **s);

//scale.c
float	ft_get_scale(t_fdf *fdf, int r, int c);
void	ft_scale(t_fdf *fdf, int r, int c);

//line.c
void	ft_plot_line(t_data data, t_point p1, t_point p2);
void	ft_print_matrix(t_fdf *fdf);

//transform.c
void	ft_set_offset(t_fdf *fdf, int *xoffset, int *yoffset);
void	ft_iso(t_fdf *fdf, t_point ***points, int r, int c);
void 	ft_center (t_fdf *fdf);

//hooks.c
int		ft_hooks(int keycode, t_fdf *vars);

// parse.c
void	ft_fill_list(int fd, t_point ***list, t_fdf *fdf);
int		ft_atoi_hex(char *nbr);

#endif
