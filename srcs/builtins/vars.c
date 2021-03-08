/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 17:02:50 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/08 12:11:25 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*vars_replacer(char *s, t_list **head)
{
	char 	*tmp;
	
	if (ft_strcmp(s, "$") == 0)
		tmp = ft_strdup("$");
	else if (!(tmp = ft_strdup(get_env(head, s + 1))))
		tmp = ft_strdup("\0");
	free(s);
	return (tmp);
}

static char		*home_replacer(char *s, char *home, t_list **head)
{
	int		len;
	char	*tmp;
	char	*username;

	username = get_env(head, "USER");
	len = ft_strlen(username);
	if (ft_strcmp(s, "~") == 0 || ft_strcmp(s + 1, username) == 0)
		tmp = ft_strdup(home);
	else
	{
		tmp = ft_strjoin(home, "/");
		if ((ft_strncmp(s + 1, username, len) == 0 && s[len + 1] == '/'))
			tmp = ft_strjoin_nl(tmp, s + (len + 2));
		else if (ft_strncmp(s, "~/", 2) == 0)
			tmp = ft_strjoin_nl(tmp, s + 2);
		else
			tmp = ft_strdup(s);
	}
	free(s);
	return (tmp);
}

char			*check_vars(t_main *m, char *s, t_list **head, int exit_status)
{
	int		x;
	char	*tmp;
	char 	**a;
	
	x = -1;
	a = ms_split_var(s);
	if (a[0])
		while (a[++x])
			if (a[x][0] == '$' || a[x][0] == '~')
			{
				if (ft_strcmp(a[x], "$?") == 0)
					a[x] = ft_itoa(exit_status);
				else if (a[x][0] == '~')
					a[x] = home_replacer(s, m->home, head);
				else
					a[x] = vars_replacer(a[x], head);
			}
	if (!(tmp = ft_merge(a)))
		malloc_error(m, s, NO_READING);
	return (tmp);
}