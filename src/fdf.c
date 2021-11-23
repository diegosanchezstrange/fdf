/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:51:32 by dsanchez          #+#    #+#             */
/*   Updated: 2021/11/23 21:08:47 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <mlx.h>
#include <math.h>
#include <fcntl.h>
#include <stdio.h>

float	ft_get_scale(t_fdf *fdf, int r, int c)
{
	float	xsize;
	float	ysize;
	float	z;

	z = 0;
	if (fdf->zoom)
	{
		fdf->zoom = 0;
		z = .5;
	}
	if (fdf->z == 0)
	{
		xsize = (1920 * 0.4) / (c - 1);
		ysize = (1080 * 0.5) / (r - 1);
	}
	else
		return (fdf->z + z);
	if (xsize <= ysize)
		return (floor(xsize + z));
	return (floor(ysize + z));
}
void	ft_scale(t_fdf *fdf, int r, int c)
{
	int	i;
	int	j;

	fdf->z = ft_get_scale(fdf, r, c);
	printf("size : %f\n", fdf->z);
	i = 0;
	j = 0;
	while (i < r)
	{
		while (j < c)
		{
			fdf->points[i][j].x *= fdf->z;
			fdf->points[i][j].y *= fdf->z;
			j++;
		}
		j = 0;
		i++;
	}
	//printf("(%d, %d) - ", fdf->points[0][1].x, fdf->points[0][1].y);
	//printf("(%d, %d)\n", fdf->points[0][2].x, fdf->points[0][2].y);
	fdf->scale = 0;
}

void	ft_set_offset(t_fdf *fdf, int *xoffset, int *yoffset)
{
	int		r;
	int		c;
	t_point	**points;

	r = fdf->h;
	c = fdf->w;
	points = fdf->points;
	if (fdf->iso || fdf->par)
	{
		*xoffset = abs((points)[0][0].x - (points)[r - 1][c - 1].x);
		*xoffset = (1920 - *xoffset)/2;
		*yoffset = abs((points)[0][c - 1].y - (points)[r - 1][c - 1].y);
		*yoffset = (1080 - *yoffset)/2;
		fdf->iso = 0;
		fdf->par = 0;
	}
	else
	{
		*xoffset = fdf->x_move;
		*yoffset = fdf->y_move;
	}
}

void	ft_iso(t_fdf *fdf, t_point ***points, int r, int c)
{ int	i; int	j;
	int	p[3];
	//float	k;

	i = 0;
	j = 0;
	while (i < r)
	{
		while (j < c)
		{
			p[0] = (*points)[i][j].x;
			p[1] = (*points)[i][j].y;
			p[2] = (*points)[i][j].z;
			(*points)[i][j].x = (p[0] - p[1]) * cos(0.523599);
			(*points)[i][j].y = -(p[2]) + sin(0.523599) * (p[0] + p[1]);
			j++;
		}
		printf("----------------------\n");
		printf("(%d, %d)\n", fdf->points[i][0].x, fdf->points[i][0].y);
		printf("(%d, %d)\n", fdf->points[i][1].x, fdf->points[i][1].y);
		printf("----------------------\n");
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

	if (fdf->scale)
		ft_scale(fdf, fdf->h, fdf->w);
	if (fdf->iso)
		ft_iso(fdf, &(fdf->points), fdf->h, fdf->w);
	ft_set_offset(fdf, &xoffset, &yoffset);
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
	printf("(%d, %d) - ", fdf->points[0][0].x, fdf->points[0][0].y);
	printf("(%d, %d) - ", fdf->points[0][1].x, fdf->points[0][1].y);
	printf("(%d, %d) - ", fdf->points[0][2].x, fdf->points[0][2].y);
	printf("(%d, %d)\n", fdf->points[0][3].x, fdf->points[0][3].y);
	mlx_put_image_to_window(fdf->mlx, fdf->win, img.img, 0, 0);
}

int	main(int argc, char **argv)
{
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
	fdf.par = 0;
	fdf.zoom = 0;
	fdf.proyec = 1;
	fdf.scale = 1;
	fdf.z = 0;
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
