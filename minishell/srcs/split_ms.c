/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   split_ms.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/17 11:53:32 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/04/25 19:03:59 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	ft_wordcount_ms(char *s, int len)
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

static char		*space_to_null(char *s, int *quoted, int len)
{
	int	i;

	i = 0;
	while (i <= len)
	{
		if ((i == 0 && s[i] == '"') || (i > 0 && s[i] == '"' &&
					s[i - 1] != '\\'))
			toggle(quoted);
		if (s[i] == ' ' && !*quoted && s[i - 1] != '\\')
			s[i] = 0;
		i++;
	}
	return (s);
}

static char	*trim_quote(char *arg)
{
	int		i;
	int		len;
	char	**splitted;

	i = 0;
	splitted = NULL;
	len = ft_strlen(arg);
	while (i <= len)
	{
		if (arg[i] == '"')
			arg[i] = 0;
		i++;
	}
	splitted = split_nulls(arg, len);
	ft_strdel(&arg);
	arg = arr_to_str(splitted);
	return (arg);
}

char			**get_args(char *s, int *quoted, char **argv)
{
	char	**args;
	size_t	i;
	size_t	len;

	args = NULL;
	len = ft_strlen(s);
	s = space_to_null(s, quoted, len);
	while (*quoted)
	{
		ft_putstr("dquote>");
		get_next_line(0, argv);
		s = end_quote(s, *argv, quoted);
		len = ft_strlen(s);
		s = space_to_null(s, quoted, len);
	}
	args = split_nulls(s, len);
	i = -1;
	while (args[++i])
		args[i] = trim_quote(args[i]);
	return (args);
}
