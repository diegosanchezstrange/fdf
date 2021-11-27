/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 18:18:52 by dsanchez          #+#    #+#             */
/*   Updated: 2021/11/13 19:08:12 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <mlx.h>

void	ft_free_all(t_fdf *fdf)
{
	t_point	**points;

	points = fdf->points;
	mlx_destroy_window(fdf->mlx, fdf->win);
	mlx_destroy_image(fdf->mlx, fdf->img.img);
	while (*points)
	{
		free(*points);
		points++;
	}
	free(fdf->points);
}

void	ft_free_split(char **s)
{
	char	**str;

	str = s;
	while (*str)
	{
		free(*str);
		str++;
	}
	free(s);
}
