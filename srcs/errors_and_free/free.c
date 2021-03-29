/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 18:27:00 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/29 12:26:59 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lexer(t_lexer *lexer)
{
    t_list *lst;
    t_list *tmp;
    t_token *tok;

    lst = lexer->tokens;
    while (lst)
    {
        tok = lst->content;
        if (tok->data)
            free(tok->data);
        free(tok);
        tmp = lst;
        lst = lst->next;
        free(tmp);
    }
    if (lexer)
        free(lexer);
    lexer = NULL;
}

static void		env_del(void *l)
{
	t_env	*tmp;

	tmp = (t_env*)l;
	free(tmp->name);
	free(tmp->value);
    free(tmp);
}

void			free_all(t_main *m)
{
	free(m->home);
	ft_lstclear(m->ehead, env_del);
	free(m->p);
	ft_free_array(m->hist);
	free(m->hist_path);
	if (m->arr)
		ft_free_array(m->arr);
	ft_free_array(m->pathdirs);
	free(m);
}