/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils_cd_ms.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/17 16:12:01 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/05/18 17:54:36 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cd_setenv(char *key, char *value, t_list **my_env)
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

void	cd_err(char *str)
{
	if (ft_strchr(str, ' '))
		ft_printf("cd: string not found in pwd: %s\n", str);
	else
		ft_printf("cd: no such file or directory: %s\n", str);
	ft_strdel(&str);
}

char	*cd_void(char *str)
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

char	*cd_minus(char *str, t_list *my_env)
{
	char	*path;

	path = NULL;
	ft_strdel(&str);
	str = get_env_value("OLDPWD", my_env);
	ft_printf("%s\n", str);
	return (str);
}
