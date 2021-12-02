/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 20:58:32 by dsanchez          #+#    #+#             */
/*   Updated: 2021/12/02 21:10:40 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

void	ft_legend(t_fdf *f)
{
	int		y;
	void	*mlx;
	void	*win;

	mlx = f->mlx;
	win = f->win;
	y = 0;
	mlx_string_put(mlx, win, 15, y += 20, 0xf9b9f2, "GUIDE: Keyboard ENG");
	mlx_string_put(mlx, win, 15, y += 20, 0xf9b9f2, "RESET : C");
	mlx_string_put(mlx, win, 15, y += 20, 0xf9b9f2, "ZOOM IN : +");
	mlx_string_put(mlx, win, 15, y += 20, 0xf9b9f2, "MOVE : Arrow Keys");
	mlx_string_put(mlx, win, 15, y += 20, 0xf9b9f2, "TOGGLE PERSPECTIVE : P");
}
