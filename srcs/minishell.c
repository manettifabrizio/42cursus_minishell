/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:39:42 by fmanetti          #+#    #+#             */
/*   Updated: 2021/01/29 14:10:06 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt()
{
	write(1, "\e[0;36m\e[1mminish # \e[0m", 25);
}

void	line_read(char	**str)
{
	char	buf[2];
	char	*tmp;
	
	if (!(*str = malloc(1)))
			return ;
	(*str)[0] = '\0';
	while (buf[0] != '\n')
	{
		// printf("a\n");
		// printf("|%s|\n", *str);
		read(1, &buf, 1);
		buf[1] = '\0';
		tmp = ft_strdup(*str);
		free(*str);
		(*str) = ft_strjoin(tmp, buf);
		free(tmp);
	}
	(*str)[ft_strlen(*str) - 1] = '\0';
}

void	builtins()
{}

void	line_execute(t_main m, char **env)
{
	if (!(search_path(m, env)))
		builtins();

}

int		main(int ac, char **av, char **env)
{
	char		*str;
	t_main		m;

	ac = 1; av = NULL;
	// ft_print_array(env);
	while (1)
	{
		prompt();
		line_read(&(m.str));
		// printf("str = %s", str);
		line_parse(&m, env);
		line_execute(m, env);
		// ft_print_list(m.ehead);
	}
	return (0);
}