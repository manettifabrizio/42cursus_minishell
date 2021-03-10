/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 20:05:42 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/10 01:20:20 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		**read_history(int fd, char **h)
{
	int		ret;
	char	*s;
	// PROBLEMA CON "echo "$?" (non lo registra al ./ successivo)
	s = NULL;
	while ((ret = get_next_separator(fd, &s)))
	{
		if (ft_isprint(s[0]))
			if (!(h = history(ft_strdup(s), h, 0, 0)))
				break;
	}
	if (ret == 0)
		h = history(ft_strdup(s), h, 0, 0);
	else if (h)
	{
		printf("minish: \033[0;31merror:\033[0m failed reading history file\n");
		ft_free_array(h);
	}
	close(fd);
	free(s);
	return (h);
}

char			**init_history()
{
	int		fd;
	char	**h;

	if (!(h = malloc(1 * sizeof(char*))))
		return (NULL); //error
	h[0] = NULL;
	if ((fd = open(".minish_history", O_RDONLY)) < 0)
		return (h);
	return (read_history(fd, h));
}