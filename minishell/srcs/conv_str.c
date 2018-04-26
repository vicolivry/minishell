/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils_ms2.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/26 10:43:55 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/04/26 17:35:54 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*trim_double_quote(char *arg, int *quoted, int len)
{
	int		i;
	char	**splitted;

	i = 0;
	splitted = NULL;
	while (i <= len)
	{
		if (arg[i] == 39 || !arg[i])
			single_toggle(quoted);
		if (arg[i] == '"' && !*quoted)
			arg[i] = 0;
		i++;
	}
	splitted = split_nulls(arg, len);
	ft_strdel(&arg);
	arg = arr_to_str(splitted);
	free_tab(splitted);
	return (arg);
}


char	*trim_single_quote(char *arg, int *quoted, int len)
{
	int		i;

	i = 0;
	while (i <= len)
	{
		if (arg[i] == '"')
			double_toggle(quoted);
		if (arg[i] == 39 && !*quoted)
			arg[i] = 0;
		i++;
	}
	return (arg);
}

char	*conv_str(char *s, int *quoted)
{
	int	len;

	*quoted = 0;
	len = ft_strlen(s);
//	conv_str(s, quoted);
//	ft_printf("IN CONV, before trim single: %s\n", s);
	s = trim_single_quote(s, quoted, len);
//	ft_printf("IN CONV, after trim single: %s\n", s);
	s = trim_double_quote(s, quoted, len);
	ft_printf("IN CONV, after: %s\n", s);

	return (s);
}
