/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:51:32 by dsanchez          #+#    #+#             */
/*   Updated: 2021/11/19 18:11:41 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <mlx.h>
#include <math.h>
#include <fcntl.h>
#include <stdio.h>

int ft_scale(int r, int c)
{
	int	xsize;
	int	ysize;

	xsize = (1920 * 0.4) / (c -1);
	ysize = (1080 * 0.5) / (r -1);
	if (xsize <= ysize)
		return (xsize);
	return (ysize);
}

void	ft_iso(t_point ***points, int r, int c)
{
	int	i;
	int	j;
	int	p[2];
	int	k;

	k = ft_scale(r, c);
	i = 0;
	j = 0;
	while (i < r)
	{
		while (j < c)
		{
			p[0] = (*points)[i][j].x * k;
			p[1] = (*points)[i][j].y * k;
			(*points)[i][j].z *= k / 4;
			(*points)[i][j].x = (p[0] - p[1]) * cos(0.523599);
			(*points)[i][j].y = -((*points)[i][j].z) + sin(0.523599) * (p[0] + p[1]);
			j++;
		}
		j = 0;
		i++;
	}
}

void ft_center (t_point ***points, int r, int c)
{
	int	xoffset;
	int	yoffset;
	int	i;
	int	j;

	ft_iso(points, r, c);
	printf("%d, %d\n", r , c);
	xoffset = abs((*points)[0][0].x - (*points)[r - 1][c - 1].x);
	xoffset = (1920 - xoffset)/2;
	yoffset = abs((*points)[0][c - 1].y - (*points)[r - 1][c - 1].y);
	yoffset = (1080 - yoffset)/2;
	i = 0;
	j = 0;
	while (i < r)
	{
		while (j < c)
		{
			(*points)[i][j].x = (*points)[i][j].x + xoffset;
			(*points)[i][j].y = (*points)[i][j].y + yoffset;
			j++;
		}
		j = 0;
		i++;
	}
}

void	ft_print_matrix(t_fdf *fdf, t_data img)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	//printf("%d, %d\n", fdf->h , fdf->w);
	//printf("(%d, %d)\n", fdf->points[0][0].x, fdf->points[0][0].y);
	ft_center(&(fdf->points), fdf->h, fdf->w);
	while (i < fdf->h)
	{
		while (j < fdf->w)
		{
			if (j < fdf->w - 1)
			{
				//printf("(%d, %d) (%d, %d)\n", fdf->points[i][j].x, fdf->points[i][j].y, fdf->points[i][j + 1].x, fdf->points[i][j + 1].y);
				ft_plot_line(img, fdf->points[i][j], fdf->points[i][j + 1]);
			}
			if (i < fdf->h - 1)
			{
				//printf("(%d, %d) (%d, %d)\n", fdf->points[i][j].x, fdf->points[i][j].y, fdf->points[i + 1][j].x, fdf->points[i + 1][j].y);
				ft_plot_line(img, fdf->points[i][j], fdf->points[i + 1][j]);
			}
			j++;
		}
		j = 0;
		i++;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, img.img, 0, 0);
	mlx_loop(fdf->mlx);
}

int	main(void)
{
	t_data	img;
	t_fdf	fdf;
	int		fd;

	fdf.points = NULL;
	fd = open("test_maps/elem-col.fdf", O_RDONLY);
	ft_fill_list(fd, &(fdf.points), &fdf);
	fdf.mlx = mlx_init();
	fdf.win = mlx_new_window(fdf.mlx, 1920, 1080, "fdf");
	img.img = mlx_new_image(fdf.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	mlx_hook(fdf.win, 2, 1L<<0, ft_hooks, &fdf);
	ft_print_matrix(&fdf, img);
	//mlx_put_image_to_window(fdf.mlx, fdf.win, img.img, 0, 0);
}
