/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils_ms.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/20 17:40:38 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/05/04 16:47:03 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	single_toggle(int *close)
{
	if (!*close)
		*close = 1;
	else
		(*close = 0);
}

void	double_toggle(int *close)
{
	if (!*close)
		*close = 2;
	else
		(*close = 0);
}

char	*end_quote(char *s, char *arg, int *quoted)
{
	int		i;

	i = 0;
	s = str_append(s, "\\");
	s = str_append(s, "n");
	while (arg[i])
	{
		if (arg[i] == '"' && (*quoted == 2 || !*quoted))
			double_toggle(quoted);
		else if (arg[i] == 39 && (*quoted == 1 || !*quoted))
			single_toggle(quoted);
		i++;
	}
	s = str_append(s, arg);
	return (s);
}

char	*arr_to_str(char **arr)
{
	int		i;
	int		j;
	int		k;
	int		len;
	char	*str;

	i = -1;
	k = 0;
	len = 0;
	str = NULL;
	while (arr[++i])
		len += ft_strlen(arr[i]);
	if (!(str = malloc(len + 1)))
		return (NULL);
	i = 0;
	while (arr[i])
	{
		j = 0;
		while (arr[i][j])
			str[k++] = arr[i][j++];
		i++;
	}
	str[k] = 0;
	return (str);
}

void	toggle_ms(int *quoted, int i, char *s)
{
	if (((i == 0 && s[i] == '"') || (i > 0 && s[i] == '"' &&
					s[i - 1] != '\\')) && *quoted != 1)
		double_toggle(quoted);
	if (((i == 0 && s[i] == 39) || (i > 0 && s[i] == 39 &&
					s[i - 1] != '\\')) && *quoted != 2)
		single_toggle(quoted);
}

size_t			ft_wordcount_ms(char *s, int len)
{
	size_t	res;
	int		i;

	i = 0;
	res = 0;
	while (i <= len)
	{
		if (!s[i] && s[i - 1])
			res++;
		i++;
	}
	return (res);
}
