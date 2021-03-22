/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starcmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:19:51 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/22 16:52:26 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		beginning_and_end(char *s, char *filename)
{
	int		i;
	t_uint	len;

	if (s[0] != '*')
	{
		i = -1;
		while (s[++i] != '*');
		if (ft_strncmp(s, filename, i) != 0)
			return (0);
	}
	len = ft_strlen(s) - 1;
	if (s[len] != '*')
	{
		i = len;
		len = ft_strlen(filename) - 1;
		printf("i = %d len = %d\n", i, len);
		while (i > 0 && s[i] != '*')
		{
			printf("s[%d] = %c file[%d] = %c\n", i, s[i], len, filename[len]);
			if (s[i] != filename[len])
				return (0);
			i--;
			len--;
		}
	}
	return (1);
}

int		starcmp(char *s, char *filename)
{
	int		i;
	int		x;
	int		c;
	char	**a;

	i = 0;
	x = 0;
	c = 0;
	a = ft_split(s, '*');
	printf("----------------------\n");
	printf("filename = %s\n", filename);
	ft_print_array(a, "a");
	while (filename[i] && a[x])
	{
		if (filename[i] == a[x][0])
		{
			c = 0;
			printf("filename + i = %s a[%d] = %s\n", filename + i, x, a[x]);
			if (ft_strncmp(filename + i, a[x], ft_strlen(a[x])) == 0)
			{
				c = 1;
				i += ft_strlen(a[x]);
				x++;
			}
		}
		i++;
	}
	printf("s[%d] = %c a[%d] = %s\n", i, s[i], x, a[x]);
	if (filename[i] == 0 && a[x])
		return (0);
	if (!(beginning_and_end(s, filename)))
		return (0);
	if (c == 1)
		return (1);
	return (0);
}