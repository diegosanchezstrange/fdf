/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:51:32 by dsanchez          #+#    #+#             */
/*   Updated: 2021/11/21 18:34:30 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <mlx.h>
#include <math.h>
#include <fcntl.h>
#include <stdio.h>

int	ft_get_scale(int r, int c)
{
	int	xsize;
	int	ysize;

	xsize = (1920 * 0.4) / (c - 1);
	ysize = (1080 * 0.5) / (r - 1);
	if (xsize <= ysize)
		return (xsize);
	return (ysize);
}
void	ft_scale(t_fdf *fdf, int r, int c)
{
	int	size;
	int	i;
	int	j;

	size = ft_get_scale(r, c);
	i = 0;
	j = 0;
	while (i < r)
	{
		while (j < c)
		{
			fdf->points[i][j].x *= size;
			fdf->points[i][j].y *= size;
			j++;
		}
		j = 0;
		i++;
	}
}

void	ft_set_offset(t_fdf *fdf, int *xoffset, int *yoffset)
{
	int		r;
	int		c;
	t_point	**points;

	r = fdf->h;
	c = fdf->w;
	points = fdf->points;
	if (fdf->iso)
	{
		*xoffset = abs((points)[0][0].x - (points)[r - 1][c - 1].x);
		*xoffset = (1920 - *xoffset)/2;
		*yoffset = abs((points)[0][c - 1].y - (points)[r - 1][c - 1].y);
		*yoffset = (1080 - *yoffset)/2;
	}else
	{
		*xoffset = fdf->x_move;
		*yoffset = fdf->y_move;
	}
}

void	ft_iso(t_point ***points, int r, int c)
{
	int	i;
	int	j;
	int	p[3];
	int	k;

	k = ft_get_scale(r, c);
	i = 0;
	j = 0;
	while (i < r)
	{
		while (j < c)
		{
			p[0] = (*points)[i][j].x;
			p[1] = (*points)[i][j].y;
			p[2] = (*points)[i][j].z * k / 4;
			(*points)[i][j].x = (p[0] - p[1]) * cos(0.523599);
			(*points)[i][j].y = -(p[2]) + sin(0.523599) * (p[0] + p[1]);
			j++;
		}
		j = 0;
		i++;
	}
}


void ft_center (t_fdf *fdf)
{
	int	xoffset;
	int	yoffset;
	int	i;
	int	j;

	//printf("scale : %d\n", fdf->scale);
	if (fdf->scale)
		ft_scale(fdf, fdf->h, fdf->w);
	//printf("(%d, %d)\n", fdf->points[0][1].x, fdf->points[0][1].y);
	if (fdf->iso)
		ft_iso(&(fdf->points), fdf->h, fdf->w);
	ft_set_offset(fdf, &xoffset, &yoffset);
	fdf->iso = 0;
	fdf->scale = 0;
	i = 0;
	j = 0;
	while (i < fdf->h)
	{
		while (j < fdf->w)
		{
			(fdf->points)[i][j].x += xoffset;
			(fdf->points)[i][j].y += yoffset;
			j++;
		}
		j = 0;
		i++;
	}
}

void	ft_print_matrix(t_fdf *fdf)
{
	int		i;
	int		j;
	t_data	img;

	i = 0;
	j = 0;
	img = fdf->img;
	ft_bzero(img.addr, SCREEN_WIDTH * SCREEN_HEIGHT * (img.bits_per_pixel /8));
	ft_center(fdf);
	while (i < fdf->h)
	{
		while (j < fdf->w)
		{
			if (j < fdf->w - 1)
				ft_plot_line(img, fdf->points[i][j], fdf->points[i][j + 1]);
			if (i < fdf->h - 1)
				ft_plot_line(img, fdf->points[i][j], fdf->points[i + 1][j]);
			j++;
		}
		j = 0;
		i++;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, img.img, 0, 0);
}

int	main(int argc, char **argv)
{
	//t_data	img;
	t_fdf	fdf;
	int		fd;

	if (argc != 2)
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (1);
	fdf.points = NULL;
	fdf.x_move = 0;
	fdf.y_move = 0;
	fdf.iso = 1;
	fdf.scale = 1;
	ft_fill_list(fd, &(fdf.points), &fdf);
	fdf.mlx = mlx_init();
	fdf.win = mlx_new_window(fdf.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "fdf");
	fdf.img.img = mlx_new_image(fdf.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	fdf.img.addr = mlx_get_data_addr(fdf.img.img,
		   	&(fdf.img.bits_per_pixel), &(fdf.img.line_length), &(fdf.img.endian));
	mlx_hook(fdf.win, 2, 1L<<0, ft_hooks, &fdf);
	ft_print_matrix(&fdf);
	mlx_loop(fdf.mlx);
}
