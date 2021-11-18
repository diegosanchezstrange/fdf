/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 19:24:33 by dsanchez          #+#    #+#             */
/*   Updated: 2021/11/12 20:02:22 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <mlx.h>
#include <stdio.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	ft_plot_line(t_data img, t_point p1, t_point p2)
{
	int	dx;
	int	dy;
	int	yi;
	int	D;

	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	D = (2 * dy) - dx;
	yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = dy * -1;
	}
	while (p1.x < p2.x)
	{
		my_mlx_pixel_put(&img, p1.x, p1.y, 0x00FF0000);
		if (D > 0)
		{
			p1.y += yi;
			D += (2 * (dy - dx));
		}
		else
			D += 2 * dy;
		p1.x += 1;
	}
}
