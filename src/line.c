/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 19:24:33 by dsanchez          #+#    #+#             */
/*   Updated: 2021/12/02 21:10:16 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <mlx.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 1920 || y >= 1080 || x < 0 || y < 0)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	ft_bigger(int x, int y)
{
	if (x < y)
		return (1);
	return (-1);
}

void	ft_plot_line(t_data img, t_point p0, t_point p1, t_point p2)
{
	int		s[2];
	int		d[2];
	int		err[2];

	s[0] = ft_bigger(p1.x, p2.x);
	s[1] = ft_bigger(p1.y, p2.y);
	d[0] = abs(p2.x - p1.x);
	d[1] = abs(p2.y - p1.y) * -1;
	err[0] = d[0] + d[1];
	while (p1.x != p2.x || p1.y != p2.y)
	{
		my_mlx_pixel_put(&img, p1.x, p1.y, get_color(p1, p0, p2));
		err[1] = 2 * err[0];
		if (err[1] >= d[1])
		{
			err[0] += d[1];
			p1.x += s[0];
		}
		if (err[1] <= d[0])
		{
			err[0] += d[0];
			p1.y += s[1];
		}
	}
}
