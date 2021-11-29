/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:54:27 by dsanchez          #+#    #+#             */
/*   Updated: 2021/11/29 19:30:47 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <math.h>
#include <stdio.h>

int	ft_check_base(char *nbr)
{
	int		i;

	if (ft_strlen(nbr) > 8 || ft_strlen(nbr) < 3)
		return (0);
	if (nbr[0] != '0' || nbr[1] != 'x')
		return (0);
	i = 2;
	while (nbr[i])
	{
		if (!ft_strchr("0123456789ABCDEFabcdef", nbr[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi_hex(char *nbr)
{
	int	i;
	int	sol;
	int	len;

	if (!ft_check_base(nbr))
		return (0xFFFFFF);
	nbr += 2;
	while (*nbr == '0')
		nbr++;
	len = ft_strlen(nbr);
	i = len - 1;
	sol = 0;
	while (i > -1)
	{
		if (ft_isdigit(nbr[i]))
			sol += (nbr[i] - 48) * pow(16, len - 1 - i);
		else
			sol += (ft_toupper(nbr[i]) - 55) * pow(16, len - 1 - i);
		i--;
	}
	return (sol);
}

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
		size++;
	return (size);
}
