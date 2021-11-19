/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 17:53:51 by dsanchez          #+#    #+#             */
/*   Updated: 2021/11/19 18:00:35 by dsanchez         ###   ########.fr       */
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
	t_data	data;
	int		W_WIDTH;
	int		W_HEIGHT;
	int		w;
	int		h;
}				t_fdf;

// free.c
void	ft_free_all(char **split, t_list **list, char *line);
void	ft_free_split(char **s);

int	ft_hooks(int keycode, t_fdf *vars);
void	ft_plot_line(t_data data, t_point p1, t_point p2);

// parse.c
void	ft_fill_list(int fd, t_point ***list, t_fdf *fdf);
int		ft_atoi_hex(char *nbr);


#endif
