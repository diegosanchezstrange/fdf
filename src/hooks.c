/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 18:44:12 by dsanchez          #+#    #+#             */
/*   Updated: 2021/11/23 19:34:40 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <mlx.h>
#include <stdio.h>

/*void	ft_rotate_x(t_fdf *f)
{
	int	i;
	int	j;
	int	p_y;
	int	p_x;

	i = 0;
	j = 0;
	while (i < fdf->h)
	{
		while (j < fdf->w)
		{
			p_x = f->points[i][j].x;
			p_y = f->points[i][j];
			
			j++;
		}
		j = 0;
		i++;
	}
}*/

void	ft_reset_points(t_fdf *fdf)
{
	t_point	**points;
	int		i;
	int		j;

	points = fdf->points;
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
			points[i][j].x = j;
			points[i][j].y = i;
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
	if (keycode == 126)
		vars->y_move = -Y_OFFSET;
	else if (keycode == 125)
		vars->y_move = Y_OFFSET;
	else if (keycode == 124)
		vars->x_move = X_OFFSET;
	else if (keycode == 123)
		vars->x_move = -X_OFFSET;
	ft_print_matrix(vars);
}

int	ft_hooks(int keycode, t_fdf *vars)
{
	float	z;

	z = 0;
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
		return (1);
	}
	else if (keycode >= 123 && keycode <= 126)
		ft_move_off(keycode, vars);
	else if (keycode == 15)
	{
		ft_reset_points(vars);
		ft_print_matrix(vars);
	}
	else if (keycode == 35)
	{
		if (vars->proyec == 1)
		{
			vars->proyec = 2;
			vars->par = 1;
		}
		else if (vars->proyec == 2)
		{
			vars->proyec = 1;
			vars->iso = 1;
		}
		ft_reset_points(vars);
		ft_print_matrix(vars);
	}
	else if (keycode == 69)
	{
		vars->scale = 1;
		vars->zoom = 1;
		vars->x_move = -50;
		vars->y_move = -50;
		z = vars->z;
		ft_reset_points(vars);
		vars->z = z;
		ft_print_matrix(vars);
	}
	return (0);
}
