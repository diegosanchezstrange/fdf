/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 20:58:20 by dsanchez          #+#    #+#             */
/*   Updated: 2021/12/02 21:10:31 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <mlx.h>
#include <math.h>

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
	fdf->scale = 0;
}
