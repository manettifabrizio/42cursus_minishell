/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 13:06:59 by fmanetti          #+#    #+#             */
/*   Updated: 2021/02/11 13:25:29 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		check_echo(char *str, char **a)
{
	int x = -1;
	while (str[++x])
		if (str[x] == '\"')
		{
			a = malloc(3 * sizeof(char*));
			a[0] = ft_strdup("echo");
			a[1] = ft_substr(str, 5, ft_strlen (str) - 5);
			a[2] = NULL;
			return (1);
		}
	return (0);
}

char	**line_read()
{
	char	*str;
	char	*tmp;
	char	**a;
	char	buf[2];
	
	buf[0] = '\0';
	if (!(str = malloc(1)))
			return (NULL);
	(str)[0] = '\0';
	while (buf[0] != '\n')
	{
		// printf("a\n");
		// printf("1|%s|\n", str);
		read(1, &buf, 1);
		buf[1] = '\0';
		tmp = ft_strdup(str);
		free(str);
		(str) = ft_strjoin(tmp, buf);
		free(tmp);
	}
	// printf("2|%s|\n", str);
	(str)[ft_strlen(str) - 1] = '\0';
	// printf("|%s|\n", str);
	// printf("|%s|\n", a[0]);
	if (check_echo(str, a))
		return (a);
	return (ft_split(str, ' '));
}