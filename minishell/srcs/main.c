/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/10 13:15:55 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/04/25 15:32:06 by volivry     ###    #+. /#+    ###.fr     */
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

int		main(int argc, const char **argv, char **env)
{
	char	**pathes;
	char	**args;
	t_list	*my_env;
	int		quoted;

	quoted = 0;
	my_env = get_env(env);
	pathes = get_pathes(env);
	args = NULL;
	while ("infinite loop")
	{
		ft_putstr("$>");
		get_next_line(0, (char**)argv);
		if (*argv)
		{
			args = get_args((char*)*argv, &quoted, (char**)argv);
			free((void*)*argv);
		}
/*		while (quoted)
		{
			ft_printf("dquote>");
			get_next_line(0, (char**)argv);
			args = end_quote(args, (char*)*argv, &quoted);
		}*/
		launch_process(args, pathes, my_env);
		if (args)
			free_tab(args);
	}
	return (0);
}
