/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 12:12:52 by viroques          #+#    #+#             */
/*   Updated: 2021/03/30 18:00:48 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char				*get_data_inside_quote(t_list **prev, t_list **cur_tok,
								t_token_type type, t_main *m)
{
	char	*tmp;
	char	*data;

	if (!(check_closing_quote(*cur_tok, type)))
		return (NULL);
	if (!(data = malloc(sizeof(char) + 1)))
		malloc_error(m, NULL, NO_READING);
	*data = t_access_tok(*cur_tok)->data[0];
	data[1] = '\0';
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
	tmp = data;
	if (!(data = ft_strjoin(tmp, t_access_tok(*cur_tok)->data)))
		malloc_error(m, NULL, NO_READING);
	free(tmp);
	del_cur_tok_and_link_next(prev, cur_tok);
	return (data);
}

static char			*get_data_word(t_list **prev, t_list **cur_tok, t_main *m)
{
	char	*data;
	char	*tmp;
	t_list 	*wild;

	wild = NULL;
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

static char			*get_data(t_list **prev, t_list **cur_tok, t_main *m)
{
	char			*data;
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
		{
			if (!(tmp = get_data_inside_quote(prev, cur_tok, type, m)))
				return (NULL);
			data = join_and_free(data, tmp);
		}
		// if (type != SQUOTE)
		// {
		// 	tmp = data;
		// 	data = check_vars(m, tmp, m->ehead, m->exit_status);
		// 	free(tmp);
		// }
	}
	return (data);
}

int					add_new_word(t_list **prev, t_list **cur_tok, t_main *m)
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
