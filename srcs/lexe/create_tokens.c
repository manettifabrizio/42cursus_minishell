/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:15:30 by viroques          #+#    #+#             */
/*   Updated: 2021/03/23 13:07:17 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int					create_tok(char *data, t_token_type type, t_lexer *lexer)
{
	t_list		*lst;
	t_token		*token;

	if (!(token = malloc(sizeof(t_token))))
		return (-1);
	token->type = type;
	if (!(token->data = ft_strdup(data)))
		return (-1);
	if (!(lst = ft_lstnew(token)))
		return (-1);
	if (!(lexer->tokens))
		lexer->tokens = lst;
	else
		ft_lstadd_back(&(lexer->tokens), lst);
	lexer->nb_tokens++;
	return (1);
}

static t_list		*generate_tok(char *data, t_token_type type, t_main *m)
{
	t_list		*lst;
	t_token		*token;

	if (!(token = malloc(sizeof(t_token))))
		malloc_error(m, NULL, NO_READING);
	token->type = type;
	if (data)
	{
		if (!(token->data = ft_strdup(data)))
			malloc_error(m, NULL, NO_READING);
	}
	else
		data = NULL;
	if (!(lst = ft_lstnew(token)))
		malloc_error(m, NULL, NO_READING);
	return (lst);
}

void				del_cur_tok_and_link_next(t_list **prev, t_list **cur_tok)
{
	if ((*cur_tok)->next)
		(*prev)->next = (*cur_tok)->next;
	else
		(*prev)->next = NULL;
	free(t_access_tok(*cur_tok)->data);
	ft_lstdelone(*cur_tok, &free);
	(*cur_tok) = (*prev)->next;
}

char				*get_data_inside_quote(t_list **prev, t_list **cur_tok, t_token_type type, t_main *m)
{
	char	*tmp;
	char	*data;

	if (!(data = malloc(sizeof(char))))
		malloc_error(m, NULL, NO_READING);
	*data = '\0';
	if (!(check_closing_quote(*cur_tok, type)))
		return (NULL);
	del_cur_tok_and_link_next(prev, cur_tok);
	while (*cur_tok && t_access_tok(*cur_tok)->type != type)
	{
		(*prev)->next = (*cur_tok)->next;
		tmp = data;
		if (!(data = ft_strjoin(tmp, t_access_tok(*cur_tok)->data)))
			malloc_error(m, NULL, NO_READING);
		free(tmp);
		free(t_access_tok(*cur_tok)->data);
		ft_lstdelone(*cur_tok, &free);
		*cur_tok = (*prev)->next;
	}
	del_cur_tok_and_link_next(prev, cur_tok);
	return (data);
}

char				*get_data_word(t_list **prev, t_list **cur_tok, t_main *m)
{
	char	*data;
	char	*tmp;

	if (!(data = malloc(sizeof(char))))
		malloc_error(m, NULL, NO_READING);
	*data = '\0';
	(*prev)->next = (*cur_tok)->next;
	tmp = data;
	if (!(data = ft_strjoin(tmp, t_access_tok(*cur_tok)->data)))
		malloc_error(m, NULL, NO_READING);
	free(tmp);
	free(t_access_tok(*cur_tok)->data);
	ft_lstdelone(*cur_tok, &free);
	*cur_tok = (*prev)->next;
	return (data);
}

char				*get_data(t_list **prev, t_list **cur_tok, t_main *m)
{
	char 			*data;
	t_token_type	type;
	char			*tmp;
	
	if (!(data = malloc(sizeof(char))))
		malloc_error(m, NULL, NO_READING);
	*data = '\0';
	while (*cur_tok && (t_access_tok(*cur_tok)->type == DQUOTE
			|| t_access_tok(*cur_tok)->type == SQUOTE
			|| t_access_tok(*cur_tok)->type == WORD))
	{
		type = t_access_tok(*cur_tok)->type;
		if (type == WORD)
			data = join_and_free(data, get_data_word(prev, cur_tok, m));
		else
			data = join_and_free(data, get_data_inside_quote(prev, cur_tok, type, m));
		if (type != SQUOTE)
		{
			tmp = data;
			data = check_vars(m, tmp, m->ehead, m->exit_status);
			free(tmp);
		}
	}
	return (data);
}

int 				add_new_word(t_list **prev, t_list **cur_tok, t_main *m)
{
	char	*data;
	t_list	*new_word;

	data = get_data(prev, cur_tok, m);
	if (!data)
		return (1);
	new_word = generate_tok(data, WORD, m);
	free(data);
	(*prev)->next = new_word;
	if (*cur_tok)
		new_word->next = *cur_tok;
	else
		new_word->next = NULL;
	*prev = new_word;
	return (0);
}