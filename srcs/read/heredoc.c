/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 23:35:25 by fmanetti          #+#    #+#             */
/*   Updated: 2021/04/05 20:51:10 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		ending(t_main *m, int fd, char *s, t_uint type)
{
	set_term_cano(m->base_term);
	m->p->multi = 0;
	close(fd);
	free(s);
	if (type == BREAK)
		remove(".heredoc");
	return (1);
}

static int		reading_heredoc(t_main *m, char **s, char *keywrd, int fd)
{
	char	buf[2];
	
	ft_bzero(buf, 2);
	read(STDOUT_FILENO, buf, 1);
	m->p->arr = split_keep(*s, '\n');
	if (!(check_key(m, s, buf)))
		*s = str_print_and_handle(*s, buf, m->p);
	if (m->p->arr)
		ft_free_array(m->p->arr);
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
	m->p->multi = 0;
	while (ft_strcmp(keywrd, s) != 0)
	{
		ft_putstr(MULTI_PROMPT);
		(s)[0] = '\0';
		while ((ret = reading_heredoc(m, &s, keywrd, fd)) > 0);
		if (ret == -1)
			return (ending(m, fd, s, BREAK));
		m->p->lpos = 0;
		m->p->hnum = 0;
	}
	m->exit_status = 0;
	return (ending(m, fd, s, NO_BREAK));
}