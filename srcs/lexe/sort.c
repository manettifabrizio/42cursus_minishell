/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 19:08:44 by viroques          #+#    #+#             */
/*   Updated: 2021/03/15 19:37:15 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			sort_heredoc_and_pipe(t_main *m, t_lexer *lexer)
{
	t_list		*cur_tok;
	t_list		*prev;
	int			type;

	cur_tok = lexer->tokens->next;
	prev = cur_tok->next;
	while (cur_tok)
	{
		type = t_access_tok(cur_tok)->type;
		if (type == DLESSER)
		{
			prev = cur_tok;
			cur_tok = cur_tok->next;
			if (!cur_tok)
				return (0);
			type = t_access_tok(cur_tok)->type;
			if (type == WORD)
				if (!heredoc(m, t_access_tok(cur_tok)->data))
					return (-1);
		}
		else if (type == PIPE || type == DPIPE || type == DAMPERSTAND)
		{
			if (!cur_tok->next)
				return (type);
		}
		prev = cur_tok;
		cur_tok = cur_tok->next;
	}
	return (0);
}

int			while_sorting(t_main *m, t_list **cur_tok, t_list **prev)
{
	int type;

	while (*cur_tok)
	{
		type = t_access_tok(*cur_tok)->type;
		if (type == SPACE || type == NEWLINE)
			del_cur_tok_and_link_next(prev, cur_tok);
		else if (type == DQUOTE || type == SQUOTE || type == WORD)
		{
			if (add_new_word(prev, cur_tok, m))
				return (t_access_tok(*cur_tok)->type);
		}
		else
		{
			*prev = *cur_tok;
			*cur_tok = (*cur_tok)->next;
		}
	}
	return (0);
}

int			sort_space_and_quote(t_lexer *lexer, t_main *m)
{
	t_list	*cur_tok;
	t_list	*prev;
	int		type;

	if ((check_pre_space(lexer) == -1))
		return (-1);
	cur_tok = lexer->tokens->next;
	prev = lexer->tokens;
	if ((type = while_sorting(m, &cur_tok, &prev)))
		return (type);
	return (0);
}

static int	replace_backslash_and_link_next(t_list **cur_tok, int len)
{
	t_list *quote;

	quote = NULL;
	t_access_tok(*cur_tok)->data[len - 1] = '\"';
	quote = (*cur_tok)->next;
	if ((*cur_tok)->next->next)
		(*cur_tok)->next = (*cur_tok)->next->next;
	else
	{
		(*cur_tok)->next = NULL;
		free(t_access_tok(quote)->data);
		ft_lstdelone(quote, &free);
		return (0);
	}
	free(t_access_tok(quote)->data);
	ft_lstdelone(quote, &free);
	return (1);
}

static void	sort_backslash_quote(t_lexer *lexer)
{
	t_list	*cur_tok;
	t_list	*prev;
	int		len;

	cur_tok = lexer->tokens->next;
	prev = lexer->tokens;
	while (cur_tok)
	{
		if (t_access_tok(cur_tok)->type == WORD)
		{
			len = ft_strlen(t_access_tok(cur_tok)->data);
			if (t_access_tok(cur_tok)->data[len - 1] == '\\')
			{
				if (cur_tok->next && t_access_tok(cur_tok->next)->type == DQUOTE)
					if (!replace_backslash_and_link_next(&cur_tok, len))
						return ;
			}
		}
		prev = cur_tok;
		cur_tok = cur_tok->next;
	}
}

int			sort_lexer(t_main *m, t_lexer *lexer)
{
	int		type;
	t_list	*head;
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->type = CHAR_NULL;
	token->data = NULL;
	head = ft_lstnew(token);
	ft_lstadd_front(&(lexer->tokens), head);
	sort_backslash_quote(lexer);
	if ((type = sort_space_and_quote(lexer, m)))
		return (type);
	if ((type = sort_heredoc_and_pipe(m, lexer)))
		return (type);
	if (lexer->tokens->next)
	{
		lexer->tokens = lexer->tokens->next;
		ft_lstdelone(head, &free);
	}
	return (0);
}
