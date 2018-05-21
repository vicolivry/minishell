/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   conv_str.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/02 11:42:39 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/05/21 13:56:07 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*convert_ms(char *s, int *quoted, int len, char *cmd)
{
	int		i;
	char	**tab;

	i = 0;
	tab = NULL;
	*quoted = 0;
	while (i <= len)
	{
		toggle_ms(quoted, i, s);
		if (!*quoted && s[i] == '\\')
			s[i] = 0;
		else if (*quoted && s[i] == '\\' && !ft_strcmp(cmd, "echo"))
			s = back_slashes_echo(s, i);
		i++;
	}
	tab = split_nulls(s, len);
	ft_strdel(&s);
	s = arr_to_str(tab);
	if (tab)
		free_tab(tab);
	return (s);
}

char		*conv_str(char *s, int *quoted, char **args, t_list *my_env)
{
	int	len;

	*quoted = 0;
	len = ft_strlen(s);
	s = convert_ms(s, quoted, len, args[0]);
	len = ft_strlen(s);
	*quoted = 0;
	s = trim_single_quote(s, quoted, len);
	*quoted = 0;
	s = trim_double_quote(s, quoted, len);
	s = dollar_conv(s, my_env);
	return (s);
}
