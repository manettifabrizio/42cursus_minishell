/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 23:35:25 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/04 18:57:32 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		heredoc(t_main *m, char *keywrd)
{
	int		fd;
	char	*s;
	char	buf[2];
	
	config_term(1, m->base_term);
	if (!(fd = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC)))
		return (0);
	if (!(s = malloc(1)))
			return (0);
	while (ft_strcmp(keywrd, s) != 0)
	{
		ft_putstr("> ");
		(s)[0] = '\0';
		ft_bzero(buf, 2);
		while (buf[0] != '\n')
		{
			read(STDOUT_FILENO, buf, 1);
			if (check_key(m, &s, buf))
			{
				if (buf[0] == CTRL_C)
					break;
			}
			else
				s = str_print_and_handle(m, s, buf, *(m->pos));
		}
		if (ft_strcmp(keywrd, s) != 0)
		{
			ft_putstr_fd(s, fd);
			ft_putchar_fd('\n', fd);
		}
		if (buf[0] == CTRL_C)
			break;
		m->pos->x = 0;
		m->pos->y = 0;
	}
	close(fd);
	free(s);
	config_term(0, m->base_term);
	return (1);
}