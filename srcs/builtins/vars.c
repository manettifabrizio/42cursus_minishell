/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 17:02:50 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/03 22:58:10 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*array_to_string(char **a)
{
	int		x;
	int		len;
	char	*s;

	x = -1;
	len = 0;
	while (a[++x])
		len += ft_strlen(a[x]);
	if (!(s = malloc((len + 1) * sizeof(char))))
		return (NULL); //error
	x = -1;
	while (a[++x])
		if (x == 0)
			ft_strcpy(s, a[x]);
		else
			ft_strcpy(s + ft_strlen(a[x - 1]), a[x]);
	s[len] = '\0';
	// ft_free_array(a);
	return (s);
}

static char		*vars_replacer(char *s, t_env *head)
{
	char 	*tmp;
	
	if (ft_strcmp(s, "$") == 0)
		tmp = ft_strdup("$");
	else if (!(tmp = ft_strdup(get_env(head, s + 1))))
		tmp = ft_strdup("\0");
	free(s);
	return (tmp);
}

char			*check_vars(char *s, t_env *head, int exit_status)
{
	int		x;
	char 	**a;
	t_env	*l;
	
	x = -1;
	a = ms_split_var(s);
	l = head;
	if (a[0])
		while (a[++x])
			if (a[x][0] == '$')
			{
				if (ft_strcmp(a[x] + 1, "?") == 0)
					a[x] = ft_itoa(exit_status);
				else
					a[x] = vars_replacer(a[x], head);
			}
	// if (!(a[0]))
	// 	return (NULL); commentati perchè non ne vedo la necessità
	return (array_to_string(a));
}