/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/10 13:15:55 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/05/15 17:11:59 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**get_pathes(char **env)
{
	int		i;
	//	int		j;
	char	*str;
	char	**pathes;

	i = 0;
	str = NULL;
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
		pathes[i] = str_append(pathes[i], "/");
		i++;
	}
	return (pathes);
}

static void	exit_ms(char **args, t_list *my_env, char **cmds, char **pathes)
{
	if (args)
		free_tab(args);
	if (pathes)
		free_tab(pathes);
	if (cmds)
		free_tab(cmds);
	if (my_env)
		free_lst(my_env);
	exit(0);
}

int		main(int argc, const char **argv, char **env)
{
	char	**pathes;
	char	**args;
	char	**cmds;
	t_list	*my_env;
	int		i;

	my_env = tab_to_lst(env);
	pathes = get_pathes(env);
	args = NULL;
	cmds = NULL;
	argc = 0;
	while ("infinite loop")
	{
		i = 0;
		print_prompt(0);
		get_next_line(0, (char**)argv);
		if (*argv)
		{
			cmds = multi_cmd((char*)*argv, (char**)argv);
			while (cmds[i])
			{
				args = get_args(cmds[i], (char**)argv, my_env);
				if (!ft_strcmp(args[0], "exit"))
					exit_ms(args, my_env, cmds, pathes);
				launch_process(args, pathes, &my_env);
				if (args)
					free_tab(args);
				i++;
			}
			ft_memdel((void**)&cmds);
		}
	}
	return (0);
}
