/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cd_ms.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/08 11:20:32 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/05/08 17:56:18 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*cd_tilt(char *str)
{
	int		i;
	char	*usr;
	char	**tab;

	i = ft_strlen(str);
	usr = NULL;
	usr = get_user();
	tab = NULL;
	str[0] = 0;
	tab = split_nulls(str, i);
	ft_strdel(&str);
	str = ft_strdup("/Users/");
	str = str_append(str, usr);
	ft_strdel(&usr);
	usr = arr_to_str(tab);
	free_tab(tab);
	str = str_append(str, usr);
	ft_strdel(&usr);
	return (str);
}

static int	cd_void(char *str)
{
	char	*usr;

	usr = NULL;
	usr = get_user();
	str = ft_strdup("/Users/");
	str = str_append(str, usr);
	chdir(str);
	ft_strdel(&str);
	ft_strdel(&usr);
	return (1);
}
/*
static char	*cd_minus(char *str, t_list **my_env)
{
	
}
*/
int	cd_ms(char **args, t_list **my_env)
{
	int		i;
	char	*str;

	i = 1;
	str = NULL;
	*my_env = *my_env;
	if (!args[1])
		return (cd_void(str));
	str = ft_strdup(args[1]);
	while (args[i++])
		str = str_append(str, args[i]);
	if (str[0] == '~')
		str = cd_tilt(str);
/*	else if (!ft_strcmp(args[1], "-"))
		str = cd_minus(str, my_env);*/
	if (chdir(str) == -1)
	{
		if (ft_strchr(str, ' '))
			ft_printf("cd: string not found in pwd: %s\n", str);
		else
			ft_printf("cd: no such file or directory: %s\n", str);
	}
	ft_strdel(&str);
	return (1);
}
