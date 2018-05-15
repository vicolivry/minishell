/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cd_ms.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/08 11:20:32 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/05/15 18:01:14 by volivry     ###    #+. /#+    ###.fr     */
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

static void	cd_setenv(char *key, char *value, t_list **my_env)
{
	t_list	*tmp;
	char	*str;

	tmp = *my_env;
	if (!tmp)
		tmp = ft_lstnew(NULL, 0);
	str = ft_strjoin(key, "=");
	while (tmp->next && !ft_strstr(tmp->content, str))
		tmp = tmp->next;
	str = str_append(str, value);
	ft_memdel(&tmp->content);
	tmp->content = ft_strdup(str);
	ft_strdel(&str);
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

static void	cd_err(char *str)
{
	if (ft_strchr(str, ' '))
		ft_printf("cd: string not found in pwd: %s\n", str);
	else
		ft_printf("cd: no such file or directory: %s\n", str);
}

static char	*cd_common(char *str, char **args, t_list *my_env)
{
	int	i;

	i = 1;
	ft_strdel(&str);
	str = get_env_value("PWD", my_env);
	str = str_append(str, "/");
	str = str_append(str, args[1]);
	while (args[i++])
		str = str_append(str, args[i]);
	return (str);
}

int	cd_ms(char **args, t_list **my_env)
{
	char	*str;
	char	*value;

	str = NULL;
	value = NULL;
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
	{
		str = getcwd(str, ft_strlen(str) + 1);
		value = get_env_value("PWD", *my_env);
		cd_setenv("OLDPWD", value, my_env);
		cd_setenv("PWD", str, my_env);
		ft_strdel(&value);
		ft_strdel(&str);
	}
	return (1);
}
