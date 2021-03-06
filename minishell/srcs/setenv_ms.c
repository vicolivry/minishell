/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   setenv_ms.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/08 11:21:35 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/05/17 16:43:41 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	setenv_ms2(char **args, t_list **my_env)
{
	t_list	*tmp;
	char	*str;

	tmp = *my_env;
	str = NULL;
	if (ft_strchr(args[1], '='))
	{
		ft_putendl("setenv: invalid argument: remove '='");
		return (1);
	}
	str = ft_strjoin(args[1], "=");
	str = to_upper_str(str);
	while (tmp->next && !ft_strstr(tmp->content, str))
		tmp = tmp->next;
	if (ft_strstr(tmp->content, str))
		ft_memdel((void**)&tmp->content);
	else
		tmp->next = ft_lstnew(NULL, 0);
	tmp->content = ft_strdup(str);
	ft_strdel(&str);
	return (1);
}

static int	setenv_ms3(char **args, t_list **my_env)
{
	t_list	*tmp;
	char	*str;

	tmp = *my_env;
	str = NULL;
	if (ft_strchr(args[1], '=') || ft_strchr(args[2], '='))
	{
		ft_putendl("setenv: invalid argument: remove '='");
		return (1);
	}
	str = ft_strjoin(args[1], "=");
	str = to_upper_str(str);
	while (tmp->next && !ft_strstr(tmp->content, str))
		tmp = tmp->next;
	if (ft_strstr(tmp->content, str))
		ft_memdel((void**)&tmp->content);
	else
		tmp->next = ft_lstnew(NULL, 0);
	str = str_append(str, args[2]);
	tmp->content = ft_strdup(str);
	ft_strdel(&str);
	return (1);
}

int			setenv_ms(char **args, t_list **my_env)
{
	t_list	*tmp;
	char	*str;

	tmp = *my_env;
	if (!tmp)
		tmp = ft_lstnew(NULL, 0);
	str = NULL;
	if (!args[1])
		ft_putendl("setenv: not enough arguments (expected one or two)");
	else if (args[1] && !args[2])
		return (setenv_ms2(args, my_env));
	else if (args[1] && args[2] && !args[3])
		return (setenv_ms3(args, my_env));
	else if (args[3])
		ft_putendl("setenv: too many arguments (expected one or two)");
	return (1);
}
