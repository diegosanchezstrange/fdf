/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 17:56:11 by dsanchez          #+#    #+#             */
/*   Updated: 2021/11/18 19:23:55 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <stdio.h>

int	ft_atoi_check(char *n)
{
	int				sign;
	char			*nptr;
	unsigned int	res;
	int				i;

	sign = 1;
	res = 0;
	i = 0;
	nptr = ft_strtrim(n, "\n");
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		res = (res * 10) + (nptr[i] - 48);
		if ((res > 2147483647 && sign == 1)
			|| (res > 2147483648 && sign == -1))
			return (0);
		i++;
	}
	free(nptr);
	return (1);
}

int	ft_aredigits(char *n)
{
	int		i;
	char	*nbr;

	i = 0;
	nbr = ft_strtrim(n, "\n");
	if (nbr[i] == '-' || nbr[i] == '+')
		i++;
	while (nbr[i])
	{
		if (!ft_isdigit(nbr[i]))
			return (0);
		i++;
	}
	if (nbr[i] == '-' || nbr[i] == '+')
		return (0);
	free(nbr);
	return (1);
}


int	ft_matrix_size(char **nbrs)
{
	int	size;

	size = 0;
	while (nbrs[size])
	{
		if (!ft_aredigits(nbrs[size]) || !ft_atoi_check(nbrs[size]))
			return (0);
		size++;
	}
	return (size);
}

t_point	*ft_new_line(char **nbrs, int y)
{	
	int		i;
	int		size;
	t_point	*res;

	i = 0;
	size = 0;
	while (nbrs[size])
		size++;
	res = (t_point *)malloc(sizeof(t_point) * (size));
	while (nbrs[i])
	{
		res[i].x = i;
		res[i].y = y;
		res[i].z = ft_atoi(nbrs[i]);
		i++;
	}
	return (res);
}

void	ft_fill_list(int fd, t_point ***list)
{
	char	*line;
	char	**nbrs;
	int		size;
	int		y;

	y = 0;
	line = get_next_line(fd);
	nbrs = ft_split(line, ' ');
	size = ft_matrix_size(nbrs);
	*list = (t_point **)malloc((size + 1) * sizeof(t_point *));
	if (!list || !size)
		return ;
	while (line)
	{
		(*list)[y] = ft_new_line(nbrs, y);
		y++;
		ft_free_split(nbrs);
		free(line);
		line = get_next_line(fd);
		nbrs = ft_split(line, ' ');
	}
	(*list)[y] = NULL;
}
