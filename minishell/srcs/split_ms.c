/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   split_ms.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/17 11:53:32 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/04/19 14:23:39 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

static size_t	word_length(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

static void		toggle(int *close)
{
	if (!*close)
		*close = 1;
	else
		(*close = 0);
}

static size_t	ft_wordcount_ms(char* s, char sp, char qte)
{
	size_t	res;
	int		i;

	res = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == qte)
		{
			i++;
			while (s[i] && s[i] != qte)
				i++;
			res++;
		}
		else if ((i == 0 && s[i] != sp) || (i > 0 && s[i] != sp &&
					(s[i - 1] == sp || s[i - 1] == qte)))
			res++;
		i++;
	}
	return (res);
}

char	**end_quote(char **args, char *s, int *close)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = NULL;
	while (args[j + 1])
		j++;
	while (s[i] && s[i] != '"')
		i++;
	tmp = ft_strsub(s, 0, i);
	if (s[i] == '"')
		toggle(close);
	args[j] = ft_strjoin(args[j], tmp);
	ft_printf("tmp : %s\nargs[j] : %s\n", tmp, args[j]);
	return (args);
}

char	**get_args(char *s, int *close)
{
	char	**args;
	size_t	count;
	size_t	i;
	size_t	j;

	args = NULL;
	count = ft_wordcount_ms(s, ' ', '"');
	if (!s || !(args = (char **)malloc(sizeof(char*) * (count + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (j < count && s[i])
	{
		if (s[i] == '"')
		{
			i++;
			toggle(close);
			args[j] = ft_strsub(s, i, word_length(s + i, '"'));
			while (s[i] && s[i] != '"')
				i++;
			if (s[i] == '"')
				toggle(close);
			j++;
		}
		else if ((i == 0 && s[i] != ' ') || (i > 0 && s[i] != ' ' &&
					(s[i - 1] == ' ' || s[i - 1] == '"')))
		{
			if (word_length(s + i, ' ') <= word_length(s + i, '"'))
				args[j] = ft_strsub(s, i, word_length(s + i, ' '));
			else
			{
				args[j] = ft_strsub(s, i, word_length(s + i, '"'));
				i++;
			}
			j++;
		}
		i++;
	}

	args[j] = NULL;
/*	j = 0;
	while (args[j])
	{
		ft_printf("args[%d]: %s\n", j, args[j]);
		j++;
	}*/
	return (args);
}
