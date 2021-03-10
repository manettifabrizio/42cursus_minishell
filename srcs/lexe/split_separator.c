/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_separator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 16:35:26 by viroques          #+#    #+#             */
/*   Updated: 2021/03/09 19:12:20 by viroques         ###   ########.fr       */
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
	char	**tab;

	i = 0;
	string = 0;
    while (s[i])
    {
        if (is_sep(charset, s[i]) || is_sep(charset, s[i + 1]))
            string++;
        i++;
    }
	if (!(tab = (char**)malloc(sizeof(char*) * (string + 1))))
		return (NULL);
	return (tab);
}

void	ft_count_letter(const char *s, char *charset, char **tab)
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
            if(!(tab[string] = malloc(sizeof(char) * (letter + 1))))
            {
                while(tab[string])
                    free(tab[string--]);
            }
            letter = 0;
            string++;
        }
        i++;
	}
}

void	ft_fill_tab(char const *s, char *charset, char **tab)
{
	int		i;
	int		string;
	int		letter;

	i = 0;
	string = 0;
	letter = 0;
	while (s[i])
	{
        tab[string][letter] = s[i];
        letter++;
        if (is_sep(charset, s[i]) || is_sep(charset, s[i + 1]))
        {
            tab[string][letter] = 0;
            string++;
            letter = 0;
        }
		i++;
	}
    tab[string] = NULL;
}

char	**ft_split_charset(const char *s, char *charset)
{
	char	**tab;

	if (!(tab = ft_count_string(s, charset)))
		return (NULL);
	ft_count_letter(s, charset, tab);
	ft_fill_tab(s, charset, tab);
	return (tab);
}