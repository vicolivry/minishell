/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_args_ms.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/26 18:13:52 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/05/17 13:27:40 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

void			toggling(char *s, int *quoted, int len)
{
	int	i;

	i = 0;
	*quoted = 0;
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
		if ((i == 0 && (s[i] == ' ' || s[i] == '\t')) || (i > 0 && (s[i] == ' '
						|| s[i] == '\t') && !*quoted && s[i - 1] != '\\'))
			s[i] = 0;
		i++;
	}
	return (s);
}

char			*slashed_arg(char *s, size_t len, char **argv, int *quoted)
{
	if (ft_strchr(s, '\\'))
		while (s[len - 1] == '\\' && !*quoted)
		{
			print_prompt(3);
			get_next_line(0, argv);
			s[len - 1] = 0;
			s = str_append(s, *argv);
			ft_strdel(argv);
			toggling(s, quoted, len);
			len = ft_strlen(s);
		}
	return (s);
}

char			*quoted_arg(char *s, size_t len, char **argv, int *quoted)
{
	while (*quoted)
	{
		*quoted == 1 ? print_prompt(1) : print_prompt(2);
		get_next_line(0, argv);
		s = end_quote(s, *argv, quoted);
		ft_strdel(argv);
		len = ft_strlen(s);
	}
	return (s);
}

char			**get_args(char *s, char **argv, t_list *my_env)
{
	char	**args;
	size_t	i;
	size_t	len;
	int		quoted;

	quoted = 0;
	args = NULL;
	len = ft_strlen(s);
	toggling(s, &quoted, len);
	s = quoted_arg(s, len, argv, &quoted);
	len = ft_strlen(s);
	s = slashed_arg(s, len, argv, &quoted);
	len = ft_strlen(s);
	s = space_to_null(s, &quoted, len);
	args = split_nulls(s, len);
	ft_strdel(&s);
	i = -1;
	while (args[++i])
		args[i] = conv_str(args[i], &quoted, args, my_env);
	return (args);
}
