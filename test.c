/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 09:55:29 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/26 14:43:24 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int ac, char **av)
{
	t_list	*head;
	t_main	*m;

	(void)ac;
	head = NULL;
	m = NULL;
	wildcard(m, ft_strdup(av[1]));
	return (0);
}
