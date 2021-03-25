/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starcmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:19:51 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/24 22:41:36 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		beginning_and_end(char *s, char *fname)
{
	int		i;
	t_uint	len;

	if (s[0] != '*')
	{
		i = -1;
		while (s[++i] != '*');
		if (ft_strncmp(s, fname, i) != 0)
			return (0);
	}
	len = ft_strlen(s) - 1;
	if (s[len] != '*')
	{
		i = len;
		len = ft_strlen(fname) - 1;
		// printf("i = %d len = %d\n", i, len);
		while (i > 0 && s[i] != '*')
		{
			// printf("s[%d] = %c file[%d] = %c\n", i, s[i], len, fname[len]);
			if (s[i] != fname[len])
				return (0);
			i--;
			len--;
		}
	}
	return (1);
}

int		starcmp(char *s, char *fname)
{
	int		i;
	int		x;
	int		c;
	char	**a;

	i = 0;
	x = 0;
	c = 0;
	a = ft_split(s, '*');
	// printf("----------------------\n");
	// printf("s = %s fname = %s\n", s, fname);
	// ft_print_array(a, "a");
	if (ft_strcmp(s, "*") == 0 && fname[0] != '.')
		return (1);
	while (fname[i] && a[x])
	{
		// printf("f[%d] = %c\n", i, fname[i]);
		if (fname[i] == a[x][0])
		{
			c = 0;
			// printf("fname + i = %s a[%d] = %s\n", fname + i, x, a[x]);
		}
		if (ft_strncmp(fname + i, a[x], ft_strlen(a[x])) == 0)
		{
			c = 1;
			i += ft_strlen(a[x]);
			x++;
		}
		else
			i++;
	}
	// printf("fname[%d] = %c a[%d] = %s\n", i, fname[i], x, a[x]);
	if (fname[i] == 0 && a[x])
		return (0);
	if (!(beginning_and_end(s, fname)))
		return (0);
	if (c == 1)
		return (1);
	return (0);
}