/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_ms.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/19 17:24:10 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/05/18 16:15:33 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*bck_slsh_qte(char *s)
{
	int		len;
	int		i;
	char	**tab;

	i = 0;
	len = ft_strlen(s);
	tab = NULL;
	while (s[i])
	{
		if (s[i] == '\\' && (s[i + 1] == '"' || s[i + 1] == 39))
			s[i] = 0;
		i++;
	}
	tab = split_nulls(s, len);
	ft_strdel(&s);
	s = arr_to_str(tab);
	if (tab)
		free_tab(tab);
	return (s);
}

static char	*tilded(char **args, t_list *my_env)
{
	if (args[1] && !args[2] && !ft_strcmp(args[1], "~"))
	{
		ft_strdel(&args[1]);
		args[1] = ft_strdup("$HOME");
		args[1] = dollar_conv(args[1], my_env);
	}
	else if (args[1] && !args[2] && !ft_strcmp(args[1], "~+"))
	{
		ft_strdel(&args[1]);
		args[1] = ft_strdup("$PWD");
		args[1] = dollar_conv(args[1], my_env);
	}
	else if (args[1] && !args[2] && !ft_strcmp(args[1], "~-"))
	{
		ft_strdel(&args[1]);
		args[1] = ft_strdup("$OLDPWD");
		args[1] = dollar_conv(args[1], my_env);
	}
	return (args[1]);
}

static int	echo_ms(char **args, t_list *my_env)
{
	int	i;

	i = 1;
	if (args[1] && !args[2] && (!ft_strcmp(args[1], "~") ||
				!ft_strcmp(args[1], "~+") || !ft_strcmp(args[1], "~-")))
		args[1] = tilded(args, my_env);
	while (args[i])
	{
		args[i] = bck_slsh_qte(args[i]);
		ft_printf("%s", args[i]);
		if (args[i + 1])
			ft_putchar(' ');
		i++;
	}
	ft_putchar('\n');
	return (1);
}

int			builtin_ms(t_list **my_env, char **args, char **pathes)
{
	if (args[0])
	{
		if (!ft_strcmp(args[0], "env") || !ft_strcmp(args[0], "/usr/bin/env"))
		{
			if (my_env && pathes)
				return (env_ms(args, *my_env, pathes));
			else
				return (env_ms(args, NULL, NULL));
		}
		else if (!ft_strcmp(args[0], "echo"))
			return (echo_ms(args, *my_env));
		else if (!ft_strcmp(args[0], "setenv"))
			return (setenv_ms(args, my_env));
		else if (!ft_strcmp(args[0], "unsetenv"))
			return (unsetenv_ms(args, my_env));
		else if (!ft_strcmp(args[0], "cd"))
			return (cd_ms(args, my_env));
	}
	return (0);
}
