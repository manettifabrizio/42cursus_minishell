/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:14:45 by viroques          #+#    #+#             */
/*   Updated: 2021/03/24 12:03:18 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_lexer		*init_lexer(t_main *m, char *s)
{
	t_lexer *lexer;

	if (!(lexer = malloc(sizeof(t_lexer))))
		malloc_error(m, NULL, NO_READING);
	lexer->tokens = NULL;
	lexer->nb_tokens = 0;
	if (!(m->arr = ft_split_charset(s, CHARSET)))
		malloc_error_lexer(m, lexer);
	return (lexer);
}

void				while_create_token(t_main *m, t_lexer *lexer)
{
	int		i;
	int		ret;

	ret = 0;
	i = 0;
	while (m->arr[i])
	{
		if ((ret = is_an_operator(m->arr[i][0], m->arr[i + 1], lexer, &i)))
			(void)ret;
		else
			ret = create_tok(m->arr[i], WORD, lexer);
		if (ret == -1)
			malloc_error_lexer(m, lexer);
		i++;
	}
}

t_lexer				*build_lexer(t_main *m, char *s)
{
	t_lexer		*lexer;
	int			type;

	lexer = init_lexer(m, s);
	while_create_token(m, lexer);
	ft_free_array(m->arr);
	if (!lexer->tokens)
		return (NULL);
	if ((type = sort_lexer(m, lexer)) > 0)
	{
		if (!(s = multilines(m, s, type)))
			return (NULL);
		free_lexer(lexer);
		lexer = NULL;
		return (build_lexer(m, s));
	}
	if (type == -1)
		return (NULL);
	if (!(m->hist = history(ft_strdup(s), m->hist, m->p->hnum)))
		malloc_error(m, s, READING);
	return (lexer);
}
