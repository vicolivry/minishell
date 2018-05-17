/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cd_ms.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/08 11:20:32 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/05/17 16:21:10 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*cd_void(char *str)
{
	char	*usr;

	ft_strdel(&str);
	usr = NULL;
	usr = get_user();
	str = ft_strdup("/Users/");
	str = str_append(str, usr);
	chdir(str);
	ft_strdel(&usr);
	return (str);
}

static char	*cd_minus(char *str, t_list *my_env)
{
	char	*path;

	path = NULL;
	ft_strdel(&str);
	str = get_env_value("OLDPWD", my_env);
	ft_printf("%s\n", str);
	return (str);
}

static char	*cd_common(char *str, char **args, t_list *my_env)
{
	int		i;
	char	*tmp;
	DIR		*dirp;

	i = 1;
	tmp = NULL;
	if ((dirp = opendir(args[1])))
	{
		closedir(dirp);
		str = ft_strdup(args[1]);
		return (str);
	}
	ft_strdel(&str);
	tmp = get_env_value("PWD", my_env);
	str = ft_strdup(tmp);
	ft_strdel(&tmp);
	str = str_append(str, "/");
	str = str_append(str, args[1]);
	while (args[i++])
		str = str_append(str, args[i]);
	return (str);
}

static void	cd_ms2(char *str, t_list **my_env)
{
	char	*value;

	value = NULL;
	str = getcwd(str, ft_strlen(str) + 1);
	value = get_env_value("PWD", *my_env);
	cd_setenv("OLDPWD", value, my_env);
	cd_setenv("PWD", str, my_env);
	ft_strdel(&value);
	ft_strdel(&str);
}

int			cd_ms(char **args, t_list **my_env)
{
	char	*str;

	str = NULL;
	if (!*my_env)
		return (1);
	if (!args[1] || args[1][0] == '~')
	{
		str = cd_void(str);
		str = args[1] && args[1][0] == '~' ? str_append(str, args[1] + 1) : str;
	}
	else if (!ft_strcmp(args[1], "-"))
		str = cd_minus(str, *my_env);
	else
		str = cd_common(str, args, *my_env);
	if (chdir(str) == -1)
		cd_err(str);
	else
		cd_ms2(str, my_env);
	return (1);
}
