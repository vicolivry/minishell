/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_ms.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/19 17:24:10 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/05/03 17:38:14 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	env_ms(char **args, t_list *my_env, char **pathes)
{
	t_list	*tmp;
	t_list	*my_env2;

	tmp = my_env;
	my_env2 = NULL;
	if (!args[1])
		while (tmp->next)
		{
			ft_printf("%s\n", tmp->content);
			tmp = tmp->next;
		}
	else if (!ft_strcmp(args[1], "-i") && !args[2])
		return (1);
/*	else if (!ft_strcmp(args[1], "-i") && args[2])
	{
		launch_process()
	}
*/
	return (1);
}

static int	echo_ms(char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		ft_printf("%s", args[i]);
		if (args[i + 1])
			ft_putchar(' ');
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
	str = NULL;
	if (!args[1])
		ft_putendl("setenv: too few arguments (expected one or two)");
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
		str = str_append(str, args[2]);
		tmp->content = ft_strdup(str);
		ft_strdel(&str);
	}
	else if (args[3])
		ft_putendl("setenv: too many arguments (expected one or two)");
	return (1);
}

static int	unsetenv_ms(char **args, t_list **my_env)
{
	t_list	*tmp;
	char	*str;

	tmp = *my_env;
	if (!args[1])
		ft_putendl("setenv: too few arguments (expected one)");
	if (args[1] && !args[2] && my_env)
	{
		str = ft_strjoin(args[1], "=");
		while (tmp->next && !ft_strstr(tmp->next->content, str))
			tmp = tmp->next;
		if (tmp->next && ft_strstr(tmp->next->content, str))
		{
			tmp->next->content_size = 0;
			tmp->next = tmp->next->next;
			ft_memdel((void**)&tmp);
		}
		ft_strdel(&str);
	}
	if (args[1] && args[2])
		ft_putendl("unsetenv : too many arguments (expected one)");
	return (1);
}

static int	cd_ms(char **args)
{
	int		i;
	char	*str;

	i = 1;
	str = NULL;
	if (!args[1])
	{
		chdir("/Users/volivry");
		return (1);
	}
	str = ft_strdup(args[1]);
	while (args[i++])
		str = ft_strjoin(str, args[i]);
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

int			builtin_ms(t_list *my_env, char **args, char **pathes)
{
	if (args[0])
	{
		if (!ft_strcmp(args[0], "env"))
			return (env_ms(args, my_env, pathes));
		else if (!ft_strcmp(args[0], "echo"))
			return (echo_ms(args));
		else if (!ft_strcmp(args[0], "setenv"))
			return (setenv_ms(args, &my_env));
		else if (!ft_strcmp(args[0], "unsetenv"))
			return (unsetenv_ms(args, &my_env));
		else if (!ft_strcmp(args[0], "cd"))
			return (cd_ms(args));
		else if (!ft_strcmp(args[0], "exit"))
		{
			if (args)
				free_tab(args);
			if (pathes)
				free_tab(pathes);
			exit(0);
		}
	}
	return (0);
}
