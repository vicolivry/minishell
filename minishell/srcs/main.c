/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/10 13:15:55 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/05/18 16:20:14 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	exit_ms(char **args, t_list *my_env, char **pathes)
{
	if (args)
		free_tab(args);
	if (pathes)
		free_tab(pathes);
	if (my_env)
		free_lst(my_env);
	exit(0);
}

static void	cmds(char **pathes, char **args, t_list *my_env, char **argv)
{
	int		i;
	char	**cmds;

	cmds = NULL;
	i = 0;
	cmds = multi_cmd((char*)*argv, (char**)argv);
	while (cmds && cmds[i])
	{
		args = get_args(cmds[i], (char**)argv, my_env);
		if (*args)
		{
			if (!ft_strcmp(args[0], "exit"))
				exit_ms(args, my_env, pathes);
			launch_process(args, pathes, &my_env);
		}
		if (args)
			free_tab(args);
		i++;
	}
	ft_memdel((void**)&cmds);
}

int			main(int argc, const char **argv, char **env)
{
	char	**pathes;
	char	**args;
	t_list	*my_env;

	my_env = tab_to_lst(env);
	pathes = NULL;
	args = NULL;
	argc = 0;
	while ("infinite loop")
	{
		if (pathes)
			free_tab(pathes);
		print_prompt(0);
		get_next_line(0, (char**)argv);
		pathes = get_pathes(my_env);
		if (*argv)
			cmds(pathes, args, my_env, (char**)argv);
	}
	return (0);
}
