/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_ms.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/19 17:24:10 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/04/20 18:40:54 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int env_ms(t_list *my_env)
{
	t_list	*tmp;

	tmp = my_env;
	while (tmp->next)
	{
		ft_printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
	return (1);
}

static int echo_ms(char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		ft_printf("%s", args[i]);
		i++;
	}
	ft_putchar('\n');
	return (1);
}

static int	setenv_ms(char **args, t_list **my_env)
{
	t_list	*tmp;
	char	*str;

	tmp = *my_env;
	if (!args[1])
		env_ms(*my_env);
	else if (args[1] && !args[2])
	{
		if (ft_strchr(args[1], '='))
		{
			ft_putendl("setenv: character '=' is forbidden in the arguments");
			return (1);
		}
		str = ft_strjoin(args[1], "=");
		while (tmp->next && !ft_strstr(tmp->content, str))
			tmp = tmp->next;
		if (ft_strstr(tmp->content, str))
			ft_memdel((void**)&tmp->content);
		else
			tmp->next = ft_lstnew(NULL, 0);
		tmp->content = ft_strdup(str);
		ft_strdel(&str);
	}
	else if (args[1] && args[2] && !args[3])
	{
		if (ft_strchr(args[1], '=') || ft_strchr(args[2], '='))
		{
			ft_putendl("setenv: character '=' is forbidden in the arguments");
			return (1);
		}
		str = ft_strjoin(args[1], "=");
		while (tmp->next && !ft_strstr(tmp->content, str))
			tmp = tmp->next;
		if (ft_strstr(tmp->content, str))
			ft_memdel((void**)&tmp->content);
		else
			tmp->next = ft_lstnew(NULL, 0);
		str = ft_strjoin(str, args[2]);
		tmp->content = ft_strdup(str);
		ft_strdel(&str);
	}
	else if (args[3])
		ft_putendl("setenv: too many arguments (expected two)");
	return (1);
}

static int	unsetenv_ms(char **args, t_list **my_env)
{
	t_list	*tmp;
	char	*str;

	tmp = *my_env;
	if (!args[1])
		return (1);
	if (args[1] && !args[2])
	{
		str = ft_strjoin(args[1], "=");
		while (tmp->next && !ft_strstr(tmp->content, str))
			tmp = tmp->next;
		if (ft_strstr(tmp->content, str))
			ft_lstdel()
	}
}

int	builtin_ms(t_list *my_env, char **args)
{
	if (!ft_strcmp(args[0], "env"))
		return (env_ms(my_env));
	else if (!ft_strcmp(args[0], "echo"))
		return (echo_ms(args));
	else if (!ft_strcmp(args[0], "setenv"))
		return (setenv_ms(args, &my_env));
	else if (!ft_strcmp(args[0], "unsetenv"))
		return (unsetenv_ms(args, &my_env));
	return (0);
}
