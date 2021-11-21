/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 18:44:12 by dsanchez          #+#    #+#             */
/*   Updated: 2021/11/21 18:26:38 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <mlx.h>
#include <stdio.h>

void	ft_reset_points(t_fdf *fdf)
{
	t_point	**points;
	int		i;
	int		j;

	points = fdf->points;
	fdf->x_move = 0;
	fdf->y_move = 0;
	fdf->scale = 1;
	fdf->iso = 1;
	i = 0;
	j = 0;
	while (i < fdf->h)
	{
		while (j < fdf->w)
		{
			points[i][j].x = j;
			points[i][j].y = i;
			j++;
		}
		j = 0;
		i++;
	}
}

int	ft_hooks(int keycode, t_fdf *vars)
{
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
		return (1);
	}
	else if (keycode == 126)
	{
		vars->y_move -= Y_OFFSET;
		ft_print_matrix(vars);
	}
	else if (keycode == 15)
	{
		ft_reset_points(vars);
		ft_print_matrix(vars);
	}
	return (0);
}
