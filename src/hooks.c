/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 18:44:12 by dsanchez          #+#    #+#             */
/*   Updated: 2021/11/29 19:19:17 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h> 
#include <mlx.h> 
#include <math.h>
#include <stdio.h>

void	ft_reset_points(t_fdf *fdf)
{
	int		i;
	int		j;

	fdf->x_move = 0;
	fdf->y_move = 0;
	fdf->scale = 1;
	fdf->z = 0;
	if (fdf->proyec == 1)
		fdf->iso = 1;
	if (fdf->proyec == 2)
		fdf->par = 1;
	i = 0;
	j = 0;
	while (i < fdf->h)
	{
		while (j < fdf->w)
		{
			fdf->points[i][j].x = j;
			fdf->points[i][j].y = i;
			j++;
		}
		j = 0;
		i++;
	}
}

void	ft_move_off(int keycode, t_fdf *vars)
{
	vars->x_move = 0;
	vars->y_move = 0;
	if (keycode == KEY_UP)
		vars->y_move = -Y_OFFSET;
	else if (keycode == KEY_DOWN)
		vars->y_move = Y_OFFSET;
	else if (keycode == KEY_RIGHT)
		vars->x_move = X_OFFSET;
	else if (keycode == KEY_LEFT)
		vars->x_move = -X_OFFSET;
	ft_print_matrix(vars);
}

void	ft_change_proyection(t_fdf *fdf)
{
	if (fdf->proyec == 1)
	{
		fdf->proyec = 2;
		fdf->par = 1;
	}
	else if (fdf->proyec == 2)
	{
		fdf->proyec = 1;
		fdf->iso = 1;
	}
	ft_reset_points(fdf);
	ft_print_matrix(fdf);
}

void	ft_zoom(t_fdf *fdf)
{
	float	z;

	z = 0;
	fdf->scale = 1;
	fdf->zoom = 1;
	fdf->x_move = -50;
	fdf->y_move = -50;
	z = fdf->z;
	ft_reset_points(fdf);
	fdf->z = z;
	ft_print_matrix(fdf);
}

int	ft_hooks(int keycode, t_fdf *vars)
{
	if (keycode == KEY_ESC)
	{
		ft_free_all(vars);
		exit(0);
		return (1);
	}
	else if (keycode == KEY_LEFT || keycode == KEY_RIGHT
		|| keycode == KEY_UP || keycode == KEY_DOWN)
		ft_move_off(keycode, vars);
	else if (keycode == KEY_C)
	{
		ft_reset_points(vars);
		ft_print_matrix(vars);
	}
	else if (keycode == KEY_P)
		ft_change_proyection(vars);
	else if (keycode == KEY_PLUS)
		ft_zoom(vars);
	return (0);
}
