/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:51:32 by dsanchez          #+#    #+#             */
/*   Updated: 2021/11/18 19:25:49 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <mlx.h>
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	t_data	img;
	t_vars	vars;
	t_point	**points;
	int		fd;

	points = NULL;
	fd = open("test_maps/42.fdf", O_RDONLY);
	ft_fill_list(fd, &points);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 640, 360, "Hello world!");
	img.img = mlx_new_image(vars.mlx, 640, 360);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);

	mlx_hook(vars.win, 2, 1L<<0, ft_hooks, &vars);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_loop(vars.mlx);
}
