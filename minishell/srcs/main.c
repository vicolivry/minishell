/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/10 13:15:55 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/05/02 17:25:47 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**get_pathes(char **env)
{
	int		i;
	int		j;
	char	*str;
	char	**pathes;

	i = 0;
	pathes = NULL;
	while (!ft_strstr(env[i], "PATH") && env[i + 1])
		i++;
	str = ft_strchr(env[i], '=') + 1;
	pathes = ft_strsplit(str, ':');
	i = 0;
	while (pathes[i])
	{
		j = 0;
		while (pathes[i][j])
			j++;
		pathes[i][j] = '/';
		i++;
	}
	return (pathes);
}

t_list	*get_env(char **env)
{
	t_list	*my_env;
	t_list	*tmp;
	int		i;

	i = 0;
	my_env = ft_lstnew(NULL, 0);
	tmp = my_env;
	while (env[i + 1])
	{
		tmp->content = ft_strdup(env[i]);
		tmp->content_size = ft_strlen(env[i]);
		tmp->next = ft_lstnew(NULL, 0);
		tmp = tmp->next;
		i++;
	}
	return (my_env);
}

int		main(int argc, const char **argv, char **env)
{
	char	**pathes;
	char	**args;
	t_list	*my_env;

	my_env = get_env(env);
	pathes = get_pathes(env);
	args = NULL;
	while ("infinite loop")
	{
		ft_putstr("\033[35m$> \033[0m");
		get_next_line(0, (char**)argv);
		if (*argv)
		{
			args = get_args((char*)*argv, (char**)argv);
			free((void*)*argv);
		}
		launch_process(args, pathes, my_env);
		if (args)
			free_tab(args);
	}
	return (0);
}
