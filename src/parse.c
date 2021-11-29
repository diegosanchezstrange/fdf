/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 17:56:11 by dsanchez          #+#    #+#             */
/*   Updated: 2021/11/29 21:35:51 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h> 
#include <stdio.h>

t_point	*ft_new_line(char **nbrs, int y)
{	
	int		i;
	int		size;
	char	**c;
	t_point	*res;

	i = 0;
	size = ft_matrix_size(nbrs);
	res = (t_point *)ft_calloc(size, sizeof(t_point));
	while (nbrs[i])
	{
		c = ft_split(nbrs[i], ',');
		if (c[1])
			res[i] = (t_point){i, y, ft_atoi(c[0]), ft_hex(c[1])};
		else if (res[i].z <= 0)
			res[i] = (t_point){i, y, ft_atoi(c[0]), 0x9381FF};
		else
			res[i] = (t_point){i, y, ft_atoi(c[0]), 0xFFC857};
		ft_free_split(colorsplit);
		i++;
	}
	return (res);
}

t_point	**ft_resize_list(t_fdf *f, char **nbrs, t_point ***list, int y)
{
	t_point	**new;
	int		i;

	i = 0;
	if (f->w != ft_matrix_size(nbrs))
		return (NULL);
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

char	**ft_split_trim(char *str, char c)
{
	char	*line;
	char	**sol;

	line = ft_strtrim(str, "\n");
	sol = ft_split(line, c);
	free(line);
	return (sol);
}

void	ft_fill_list(int fd, t_point ***list, t_fdf *fdf)
{
	char	*line;
	char	**nbrs;
	int		y;

	y = 0;
	line = get_next_line(fd);
	nbrs = ft_split_trim(line, ' ');
	fdf->w = ft_matrix_size(nbrs);
	*list = (t_point **)malloc(2 * sizeof(t_point *));
	if (!list || !fdf->w)
		return ;
	while (line)
	{
		(*list)[y] = ft_new_line(nbrs, y);
		y++;
		*list = ft_resize_list(fdf, nbrs, list, y);
		ft_free_split(nbrs);
		free(line);
		if (*list == NULL)
			return ;
		line = get_next_line(fd);
		nbrs = ft_split_trim(line, ' ');
	}
	fdf->h = y;
	(*list)[y] = NULL;
}
