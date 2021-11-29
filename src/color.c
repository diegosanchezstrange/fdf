/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 19:23:30 by dsanchez          #+#    #+#             */
/*   Updated: 2021/11/29 19:24:05 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

double	percent(int start, int end, int current)
{
	double	placement;
	double	distance;

	placement = current - start;
	distance = end - start;
	if (distance == 0)
		return (1.0);
	else
		return (placement / distance);
}

int	get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

int	get_color(t_point current, t_point start, t_point end)
{
	int		red;
	int		green;
	int		blue;
	double	per;

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
