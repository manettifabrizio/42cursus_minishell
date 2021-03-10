/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 23:35:25 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/10 15:37:56 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		ending(t_main *m, int fd, char *s, int ret)
{
	set_term_cano(m->base_term);
	close(fd);
	free(s);
	if (ret == BREAK)
		remove(".heredoc");
	return (ret);
}

static int		reading_heredoc(t_main *m, char **s, char *keywrd, int fd)
{
	char	buf[2];
	
	read(STDOUT_FILENO, buf, 1);
	if (!(check_key_heredoc(m, s, buf)))
		*s = str_print_and_handle(m, *s, buf, *(m->pos));
	if (buf[0] == CTRL_C || buf[0] == CTRL_D)
		return (-1);
	if (buf[0] == '\n')
	{
		if (ft_strcmp(keywrd, *s) != 0)
		{
			ft_putstr_fd(*s, fd);
			ft_putchar_fd('\n', fd);
		}
		return (0);
	}
	return (1);
}

int		heredoc(t_main *m, char *keywrd)
{
	int		fd;
	char	*s;
	int		ret;
	
	set_term_noncano();
	if (!(fd = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC)))
		return (0);
	s = ft_strdup("");
	while (ft_strcmp(keywrd, s) != 0)
	{
		ft_putstr("> ");
		(s)[0] = '\0';
		while ((ret = reading_heredoc(m, &s, keywrd, fd)) > 0);
		if (ret == -1)
			return (ending(m, fd, s, BREAK));
		m->pos->x = 0;
		m->pos->y = 0;
	}
	m->exit_status = 0;
	return (ending(m, fd, s, NO_BREAK));
}