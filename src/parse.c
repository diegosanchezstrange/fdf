/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 17:56:11 by dsanchez          #+#    #+#             */
/*   Updated: 2021/11/29 19:29:35 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h> 
#include <stdio.h>

t_point	*ft_new_line(char **nbrs, int y)
{	
	int		i;
	int		size;
	char	**colorsplit;
	t_point	*res;

	i = 0;
	size = ft_matrix_size(nbrs);
	res = (t_point *)ft_calloc(size, sizeof(t_point));
	while (nbrs[i])
	{
		colorsplit = ft_split(nbrs[i], ',');
		res[i].x = i;
		res[i].y = y;
		res[i].z = ft_atoi(colorsplit[0]);
		if (colorsplit[1])
			res[i].color = ft_atoi_hex(ft_strtrim(colorsplit[1], "\n"));
		else if (res[i].z <= 0)
			res[i].color = 0x9381FF;
		else
			res[i].color = 0xFFC857;
		ft_free_split(colorsplit);
		i++;
	}
	return (res);
}

t_point	**ft_resize_list(t_point ***list, int y)
{
	t_point	**new;
	int		i;

	i = 0;
	new = (t_point **)malloc((2 + y) * sizeof(t_point *));
	if (!new)
		return (NULL);
	while (i != y)
	{
		new[i] = (*list)[i];
		i++;
	}
	free(*list);
	return (new);
}

void	ft_fill_list(int fd, t_point ***list, t_fdf *fdf)
{
	char	*line;
	char	**nbrs;
	int		y;

	y = 0;
	line = get_next_line(fd);
	nbrs = ft_split(line, ' ');
	fdf->w = ft_matrix_size(nbrs);
	*list = (t_point **)malloc(2 * sizeof(t_point *));
	if (!list || !fdf->w)
		return ;
	while (line)
	{
		(*list)[y] = ft_new_line(nbrs, y);
		y++;
		*list = ft_resize_list(list, y);
		if (!list)
			return ;
		ft_free_split(nbrs);
		free(line);
		line = get_next_line(fd);
		nbrs = ft_split(line, ' ');
	}
	fdf->h = y;
	(*list)[y] = NULL;
}
