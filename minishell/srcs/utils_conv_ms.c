/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils_conv_ms.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/02 15:25:09 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/05/15 18:01:59 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**split_nulls(char *s, int len)
{
	char	**args;
	int		count;
	int		i;
	int		j;

	args = NULL;
	i = 0;
	j = 0;
	count = ft_wordcount_ms(s, len);
	if (!s || !(args = (char**)malloc(sizeof(char*) * (count + 1))))
		return (NULL);
	while (i <= len)
	{
		if (s[i])
		{
			args[j] = ft_strsub(s, i, ft_strlen(s + i));
			i += ft_strlen(s + i) + 1;
			*s = *s + i;
			j++;
		}
		else
			i++;
	}
	args[j] = NULL;
	return (args);
}

char	*trim_double_quote(char *arg, int *quoted, int len)
{
	int		i;
	char	**splitted;

	i = 0;
	splitted = NULL;
	while (i <= len)
	{
		if (!arg[i])
			single_toggle(quoted);
		if (arg[i] == '\\' && arg[i + 1] == '"')
		{
			arg[i] = 0;
			i++;
		}
		else if ((i == 0 && arg[i] == '"') || (i > 0 && arg[i] == '"'
					&& !*quoted && arg[i - 1] != '\\'))
			arg[i] = 0;
		i++;
	}
	splitted = split_nulls(arg, len);
	ft_strdel(&arg);
	arg = arr_to_str(splitted);
	if (splitted)
		free_tab(splitted);
	return (arg);
}

char	*trim_single_quote(char *arg, int *quoted, int len)
{
	int		i;

	i = 0;
	while (i <= len)
	{
		if ((i == 0 && arg[i] == '"') || (i > 0 && arg[i] == '"'
					&& arg[i - 1] != '\\'))
			double_toggle(quoted);
		if (arg[i] == 39 && !*quoted)
			arg[i] = 0;
		i++;
	}
	return (arg);
}

char	*back_slashes_echo(char *s, int i)
{
	if (ft_strchr(BCK_SLASHES, s[i + 1]))
		s[i] = 0;
	if (s[i + 1] == 't')
		s[i + 1] = 9;
	else if (s[i + 1] == 'n')
		s[i + 1] = 10;
	else if (s[i + 1] == 'v')
		s[i + 1] = 11;
	else if (s[i + 1] == 'r')
		s[i + 1] = 13;
	else if (s[i + 1] == '\\')
		s[i + 1] = 92;
	else if (s[i + 1] == 's')
		s[i + 1] = 32;
	else if (s[i + 1] == 'b')
		s[i + 1] = 8;
	return (s);
}
