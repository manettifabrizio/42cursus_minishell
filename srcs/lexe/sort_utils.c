/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 19:16:25 by viroques          #+#    #+#             */
/*   Updated: 2021/03/22 16:26:22 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			check_closing_quote(t_list *tokens, t_token_type type)
{
	t_list	*cur_tok;

	cur_tok = tokens->next;
	while (cur_tok)
	{
		if (t_access_tok(cur_tok)->type == type)
			return (1);
		cur_tok = cur_tok->next;
	}
	return (0);
}

int			check_pre_space(t_lexer *lexer)
{
	t_list		*cur_tok;
	t_list		*prev;

	cur_tok = lexer->tokens;
	prev = NULL;
	while (cur_tok && (t_access_tok(cur_tok)->type == SPACE
			|| t_access_tok(cur_tok)->type == NEWLINE))
	{
		prev = cur_tok;
		cur_tok = cur_tok->next;
		free(t_access_tok(prev)->data);
		ft_lstdelone(prev, &free);
	}
	if (cur_tok)
		lexer->tokens = cur_tok;
	else
		return (-1);
	return (0);
}

void		word_interpolation(t_main *m, t_list **cur_tok, t_list **prev)
{
	char	*tmp;

	tmp = t_access_tok(*cur_tok)->data;
	t_access_tok(*cur_tok)->data = check_vars(m, tmp, m->ehead, m->exit_status);
	free(tmp);
	*prev = *cur_tok;
	*cur_tok = (*cur_tok)->next;
}

char		*join_and_free(char *s1, char *s2)
{
	char	*data;

	data = ft_strjoin(s1, s2);
	free(s2);
	free(s1);
	return (data);
}