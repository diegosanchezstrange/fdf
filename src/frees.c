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

void	ft_free_all(char **split, t_list **list, char *line)
{
	ft_free_split(split);
	free(line);
	ft_lstclear(list, free);
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
