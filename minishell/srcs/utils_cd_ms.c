/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils_cd_ms.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/17 16:12:01 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/05/17 16:21:53 by volivry     ###    #+. /#+    ###.fr     */
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
}
