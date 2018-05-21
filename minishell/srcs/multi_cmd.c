/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   multi_cmd.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/07 10:18:21 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/05/21 15:29:54 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*sc_to_null(char *s, int *quoted, int len)
{
	int	i;

	i = 0;
	while (i <= len)
	{
		toggle_ms(quoted, i, s);
		if ((i == 0 && s[i] == ';') || (i > 0 && s[i] == ';' && !*quoted &&
					s[i - 1] != '\\'))
			s[i] = 0;
		i++;
	}
	return (s);
}

char		**multi_cmd(char *s, char **argv)
{
	char	**cmds;
	size_t	len;
	int		quoted;

	quoted = 0;
	cmds = NULL;
	len = ft_strlen(s) - 1;
	toggling(s, &quoted, len);
	s = quoted_arg(s, len, argv, &quoted);
	len = ft_strlen(s);
	s = slashed_arg(s, len, argv, &quoted);
	len = ft_strlen(s);
	s = sc_to_null(s, &quoted, len);
	cmds = split_nulls(s, len);
	ft_strdel(&s);
	return (cmds);
}
