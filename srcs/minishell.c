/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:39:42 by fmanetti          #+#    #+#             */
/*   Updated: 2021/02/11 09:53:45 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt()
{
	write(1, "\e[0;36m\e[1mminish # \e[0m", 24);
}

char	**line_read()
{
	char	*str;
	char	*tmp;
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
	int x = -1;
	char **a;
	while (str[++x])
		if (str[x] == '\"')
		{
			a = malloc(3 * sizeof(char*));
			a[0] = ft_strdup("echo");
			a[1] = ft_substr(str, 5, ft_strlen (str) - 5);
			a[2] = NULL;
			return (a);
		}
	return (ft_split(str, ' '));
}

void	line_execute(t_main *m, char **env)
{
	if (!(builtins(m)))
	{
		// printf("Error: builtin not found");
		if (!(search_path(*m, env)))
			printf("Error: command not found\n"); //ERROR: command not found
	}
	// ms_print_list(m->ehead);
}

int		main(int ac, char **av, char **env)
{
	char		*str;
	t_main		m;
	int x;

	ac = 1; av = NULL;
	// ft_print_array(env);
	line_parse(&m, env);
	while (1)
	{
		prompt();
		m.arr = line_read();
		// ft_print_array(m.arr);
		// if (strcmp("echo", m.arr[0]))
		// 		m.arr[1] = av[1]
		// printf("str = %s", str);
		if ((m.arr)[0])
			line_execute(&m, env);
		// ms_print_list(m.ehead);
	}
	return (0);
}