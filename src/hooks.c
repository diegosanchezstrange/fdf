/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 18:44:12 by dsanchez          #+#    #+#             */
/*   Updated: 2021/11/12 19:04:28 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <mlx.h>

int	ft_hooks(int keycode, t_vars *vars)
{
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
		return (1);
	}
	return (0);
}
