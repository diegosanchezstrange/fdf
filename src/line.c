/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 19:24:33 by dsanchez          #+#    #+#             */
/*   Updated: 2021/11/21 18:34:58 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <mlx.h>
#include <stdio.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 1920 || y >= 1080 || x < 0 || y < 0)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	ft_bigger(int x, int y)
{
	if (x < y)
		return (1);
	return (-1);
}

double percent(int start, int end, int current)
{
    double placement;
    double distance;

    placement = current - start;
    distance = end - start;
    return ((distance == 0) ? 1.0 : (placement / distance));
}

int get_light(int start, int end, double percentage)
{
    return ((int)((1 - percentage) * start + percentage * end));
}

int get_color(t_point current, t_point start, t_point end)
{
    int     red;
    int     green;
    int     blue;
    double  per;

    if (current.color == end.color)
        return (current.color);
    if (abs(end.x - start.x) > abs(end.y - start.y))
        per = percent(start.x, end.x, current.x);
    else
        per = percent(start.y, end.y, current.y);
    red = get_light((start.color >> 16) & 0xFF, (end.color >> 16) & 0xFF, per);
    green = get_light((start.color >> 8) & 0xFF, (end.color >> 8) & 0xFF, per);
    blue = get_light(start.color & 0xFF, end.color & 0xFF, per);
    return ((red << 16) | (green << 8) | blue);
}

void	ft_plot_line(t_data img, t_point p1, t_point p2)
{
	int	s[2];
	int	d[2];
	int	err[2];
	t_point	p0;

	s[0] = ft_bigger(p1.x, p2.x);
	s[1] = ft_bigger(p1.y, p2.y);
	d[0] = abs(p2.x - p1.x);
	d[1] = abs(p2.y - p1.y) * -1;
	err[0] = d[0] + d[1];
	p0 = p1;
	/*printf("--------------------------\n");
	printf("p1: (%d, %d, %d, %x)\n", p1.x, p1.y, p1.z, p1.color);
	printf("p2: (%d, %d, %d, %x)\n", p2.x, p2.y, p2.z, p2.color);
	printf("--------------------------\n");*/
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

