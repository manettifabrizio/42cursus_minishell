/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 18:27:00 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/08 19:52:12 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lexer(t_list *lst_tokens)
{
    t_list *lst;
    t_list *tmp;
    t_token *tok;

    lst = lst_tokens;
    while (lst)
    {
        tok = lst->content;
        free(tok->data);
        free(tok);
        tmp = lst;
        lst = lst->next;
        free(tmp);
    }
}

static void		env_del(void *l)
{
	t_env	*tmp;

	tmp = (t_env*)l;
	free(tmp->name);
	free(tmp->value);
}

void			free_all(t_main *m)
{
	free(m->home);
	ft_lstclear(m->ehead, env_del);
	free(m->pos);
	ft_free_array(m->hist);
	free(m->hist_path);
	ft_free_array(m->arr);
	ft_free_array(m->pathdirs);
	free(m);
}