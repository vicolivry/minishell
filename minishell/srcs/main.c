/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/10 13:15:55 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/05/04 17:06:00 by volivry     ###    #+. /#+    ###.fr     */
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
	if (!env[0])
		return (NULL);
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

int		main(int argc, const char **argv, char **env)
{
	char	**pathes;
	char	**args;
	char	**cmds;
	t_list	*my_env;

	my_env = tab_to_lst(env);
	pathes = get_pathes(env);
	args = NULL;
	cmds = NULL;
	while ("infinite loop")
	{
		ft_putstr("\033[35m$> \033[0m");
		get_next_line(0, (char**)argv);
		if (*argv)
		{
			cmds = ft_strsplit((char*)*argv, ';');
			free((void*)*argv);
		}
		while (*cmds)
		{
				args = get_args(*cmds, (char**)argv);
				launch_process(args, pathes, my_env);
			if (args)
				free_tab(args);
			cmds += 1;
		}
	}
	return (0);
}
