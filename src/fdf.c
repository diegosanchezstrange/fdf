/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:51:32 by dsanchez          #+#    #+#             */
/*   Updated: 2021/11/25 21:35:11 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <mlx.h>
#include <math.h>
#include <fcntl.h>

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

void	ft_init_program(t_fdf *fdf)
{
	fdf->points = NULL;
	fdf->x_move = 0;
	fdf->y_move = 0;
	fdf->iso = 1;
	fdf->par = 0;
	fdf->zoom = 0;
	fdf->proyec = 1;
	fdf->scale = 1;
	fdf->z = 0;
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
	ft_init_program(&fdf);
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
