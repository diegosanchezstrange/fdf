/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 17:56:11 by dsanchez          #+#    #+#             */
/*   Updated: 2021/12/02 21:10:22 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h> 

void	ft_error(t_fdf *f, char **nbrs, char *line)
{
	ft_free_split(nbrs);
	free(line);
	ft_free_all(f);
	exit(1);
}

t_point	*ft_new_line(t_fdf *f, char **nbrs)
{	
	int		i;
	char	**c;
	t_point	*res;

	i = 0;
	res = (t_point *)ft_calloc(ft_matrix_size(nbrs), sizeof(t_point));
	while (nbrs[i])
	{
		c = ft_split(nbrs[i], ',');
		if (c[1])
			res[i] = (t_point){i, f->h, ft_atoi(c[0]), ft_hex(c[1])};
		else if (ft_atoi(c[0]) <= 0)
			res[i] = (t_point){i, f->h, ft_atoi(c[0]), 0x9381FF};
		else
			res[i] = (t_point){i, f->h, ft_atoi(c[0]), 0xFFC857};
		if (!ft_aredigits(c[0]))
		{
			ft_free_split(c);
			free(res);
			return (NULL);
		}
		ft_free_split(c);
		i++;
	}
	return (res);
}

t_point	**ft_resize_list(t_fdf *f, t_point ***list)
{
	t_point	**new;
	int		i;

	i = 0;
	new = (t_point **)malloc((2 + f->h) * sizeof(t_point *));
	if (!new)
		return (NULL);
	while (i != f->h)
	{
		new[i] = (*list)[i];
		i++;
	}
	new[i] = NULL;
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

	fdf->h = 0;
	line = get_next_line(fd);
	nbrs = ft_split_trim(line, ' ');
	fdf->w = ft_matrix_size(nbrs);
	*list = (t_point **)malloc(2 * sizeof(t_point *));
	if (!list || !fdf->w)
		return ;
	while (line)
	{
		(*list)[fdf->h + 1] = NULL;
		(*list)[fdf->h] = ft_new_line(fdf, nbrs);
		if ((*list)[fdf->h] == NULL || ft_matrix_size(nbrs) != fdf->w)
			ft_error(fdf, nbrs, line);
		fdf->h++;
		*list = ft_resize_list(fdf, list);
		ft_free_split(nbrs);
		free(line);
		if (*list == NULL)
			return ;
		line = get_next_line(fd);
		nbrs = ft_split_trim(line, ' ');
	}
}
