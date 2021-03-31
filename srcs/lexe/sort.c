/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 12:23:06 by viroques          #+#    #+#             */
/*   Updated: 2021/03/31 12:19:42 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int					sort_heredoc_and_wildcard(t_main *m, t_lexer *lexer)
{
	t_list		*cur_tok;
	t_list		*prev;
	t_list		*wild;
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
		else if (type == WILDCARD)
		{
			wild = wildcard(m ,t_access_tok(cur_tok)->data);
			(prev)->next = wild;
			wild = ft_lstlast(wild);
			wild->next = (cur_tok)->next;
			cur_tok = wild;
		}
		prev = cur_tok;
		cur_tok = cur_tok->next;
	}
	return (0);
}

int					while_sorting(t_main *m, t_list **cur_tok, t_list **prev)
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

int					sort_space_and_quote(t_lexer *lexer, t_main *m)
{
	t_list	*cur_tok;
	t_list	*prev;
	int		type;

	cur_tok = lexer->tokens->next;
	prev = lexer->tokens;
	if ((type = while_sorting(m, &cur_tok, &prev)))
		return (type);
	return (0);
}


void		print_lst(t_list *lst)
{
	t_list *toto;

	toto = lst;
	printf("\n LEXER \n");
	while (toto)
	{
		t_token *t = toto->content;
		printf("%s     ---------- %u\n", t->data, t->type);
		toto = toto->next;
	}
}

static void			type_wildcard(t_lexer *lexer)
{
	t_list	*cur_tok;
	t_list	*prev;

	cur_tok = lexer->tokens->next;
	prev = lexer->tokens;
	while (cur_tok)
	{
		if (ft_strrchr(t_access_tok(cur_tok)->data, '*')
			&& t_access_tok(prev)->type == SPACE)
				t_access_tok(cur_tok)->type = WILDCARD;
		prev = cur_tok;
		cur_tok = cur_tok->next;
	}
}

int					 sort_lexer(t_main *m, t_lexer *lexer)
{
	int		type;
	t_list	*head;
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->type = CHAR_NULL;
	token->data = NULL;
	head = ft_lstnew(token);
	ft_lstadd_front(&(lexer->tokens), head);
	if ((check_pre_space(lexer) == -1))
		return (-1);
	type_wildcard(lexer);
	if ((type = sort_space_and_quote(lexer, m)))
		return (type);
	if ((type = sort_heredoc_and_wildcard(m, lexer)))
		return (type);
	if (lexer->tokens->next)
	{
		lexer->tokens = lexer->tokens->next;
		ft_lstdelone(head, &free);
	}
	return (0);
}
