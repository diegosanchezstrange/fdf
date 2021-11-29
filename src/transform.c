/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 21:31:05 by dsanchez          #+#    #+#             */
/*   Updated: 2021/11/29 19:31:54 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <mlx.h>
#include <math.h>

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
		*xoffset = (1920 - *xoffset) / 2;
		*yoffset = abs((points)[0][c - 1].y - (points)[r - 1][c - 1].y);
		*yoffset = (1080 - *yoffset) / 2;
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
{
	int	i;
	int	j;
	int	p[3];

	i = 0;
	j = 0;
	while (i < r)
	{
		while (j < c)
		{
			p[0] = (*points)[i][j].x;
			p[1] = (*points)[i][j].y;
			p[2] = (*points)[i][j].z * fdf->z / 4;
			(*points)[i][j].x = (p[0] - p[1]) * cos(0.523599);
			(*points)[i][j].y = -(p[2]) + sin(0.523599) * (p[0] + p[1]);
			j++;
		}
		j = 0;
		i++;
	}
}

void	ft_center(t_fdf *fdf)
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
