/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_separator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 16:35:26 by viroques          #+#    #+#             */
/*   Updated: 2021/03/18 10:19:25 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     is_sep(char *charset, char c)
{
    int     i;

    i = 0;
    while (charset[i])
    {
        if (charset[i] == c)
            return (1);
        i++;
    }
    if (charset[i] == c)
        return (1);
    return (0);
}

char	**ft_count_string(const char *s, char *charset)
{
	int		string;
	int		i;
	char	**tb;

	i = 0;
	string = 0;
    while (s[i])
    {
        if (is_sep(charset, s[i]) || is_sep(charset, s[i + 1]))
            string++;
        i++;
    }
	if (!(tb = (char**)malloc(sizeof(char*) * (string + 1))))
		return (NULL);
	return (tb);
}

void	ft_count_letter(const char *s, char *charset, char **tb)
{
	int		i;
	int		string;
	int		letter;

	i = 0;
	string = 0;
	letter = 0;
	while (s[i])
	{
		letter++;
        if (is_sep(charset, s[i]) || is_sep(charset, s[i + 1]))
        {
            if(!(tb[string] = malloc(sizeof(char) * (letter + 1))))
            {
                while(tb[string])
                    free(tb[string--]);
            }
            letter = 0;
            string++;
        }
        i++;
	}
}

void	ft_fill_tab(char const *s, char *charset, char **tb)
{
	int		i;
	int		string;
	int		letter;

	i = 0;
	string = 0;
	letter = 0;
	while (s[i])
	{
        tb[string][letter] = s[i];
        letter++;
        if (is_sep(charset, s[i]) || is_sep(charset, s[i + 1]))
        {
            tb[string][letter] = 0;
            string++;
            letter = 0;
        }
		i++;
	}
    tb[string] = NULL;
}

char	**ft_split_charset(const char *s, char *charset)
{
	char	**tb;

	if (!(tb = ft_count_string(s, charset)))
		return (NULL);
	ft_count_letter(s, charset, tb);
	ft_fill_tab(s, charset, tb);
	return (tb);
}