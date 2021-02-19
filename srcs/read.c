/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 13:06:59 by fmanetti          #+#    #+#             */
/*   Updated: 2021/02/17 18:24:46 by fmanetti         ###   ########.fr       */
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

char	**line_read(struct termios *base_term)
{
	char	*str;
	char	*tmp;
	char	**a;
	char	buf[2];
	
	buf[0] = '\0';
	buf[1] = '\0';
	if (!(str = malloc(1)))
			return (NULL);
	(str)[0] = '\0';
	while (buf[0] != '\n')
	{
		read(1, &buf, 1);
		buf[1] = '\0';
		ft_putchar(buf[0]);
		if (buf[0] == CTRL_C)
		{
			ft_putchar('\n');
			free(str);
			str = ft_strdup("\0");
			break;
		}
		if (buf[0] == CTRL_D)
		{
			set_term(0, base_term);
			ft_putstr("exit\n");
			exit(EXIT_SUCCESS);
		}
		if (buf[0] == CTRL_BSLASH)
			ft_putstr("\b\b");
		tmp = ft_strdup(str);
		free(str);
		(str) = ft_strjoin(tmp, buf);
		free(tmp);
	}
	if ((ft_strlen(str) - 1) >= 0)
		(str)[ft_strlen(str) - 1] = '\0';
	set_term(0, base_term);
	if (check_echo(str, a))
		return (a);
	return (ft_split(str, ' '));
}