/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_args_ms.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/26 18:13:52 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/05/03 16:17:11 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

static void		toggling(char *s, int *quoted, int len)
{
	int	i;

	i = 0;
	while (i <= len)
	{
		toggle_ms(quoted, i, s);
		i++;
	}
}

static char		*space_to_null(char *s, int *quoted, int len)
{
	int	i;

	i = 0;
	while (i <= len)
	{
		toggle_ms(quoted, i, s);
		if (s[i] == ' ' && !*quoted && s[i - 1] != '\\')
			s[i] = 0;
		i++;
	}
	return (s);
}

static char		*slashed_arg(char *s, size_t len, char **argv)
{
	while (s[len - 1] == '\\')
	{
		ft_putstr("\033[35m> \033[0m");
		get_next_line(0, argv);
		s[len - 1] = 0;
		s = str_append(s, *argv);
		len = ft_strlen(s);
	}
	return (s);
}

char			**get_args(char *s, char **argv)
{
	char	**args;
	size_t	i;
	size_t	len;
	int		quoted;

	quoted = 0;
	args = NULL;
	len = ft_strlen(s);
	toggling(s, &quoted, len);
	while (quoted)
	{
		quoted == 1 ? ft_putstr("\033[35mquote> \033[0m") :
			ft_putstr("\033[35mdquote> \033[0m");
		get_next_line(0, argv);
		s = end_quote(s, *argv, &quoted);
		len = ft_strlen(s);
	}
	s = slashed_arg(s, len, argv);
	len = ft_strlen(s);
	s = space_to_null(s, &quoted, len);
	args = split_nulls(s, len);
	i = -1;
	while (args[++i])
		args[i] = conv_str(args[i], &quoted, args);
	return (args);
}
