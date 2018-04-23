/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/10 13:15:55 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/04/23 18:38:57 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**get_pathes(char **env)
{
	int		i;
	char	*str;
	char	**pathes;

	i = 0;
	pathes = NULL;
	while (!ft_strstr(env[i], "PATH") && env[i + 1])
		i++;
	str = ft_strchr(env[i], '=') + 1;
	pathes = ft_strsplit(str, ':');
	return (pathes);
}

int		main(int argc, const char **argv, char **env)
{
	char	**pathes;
	char	**args;
	t_list	*my_env;
	int		close;

	close = 0;
	my_env = get_env(env);
	pathes = get_pathes(env);
	args = NULL;
	while (101)
	{
		ft_putstr("$>");
		get_next_line(0, (char**)argv);
		if (*argv)
		{
			args = get_args((char*)*argv, &close);
			free((void*)*argv);
		}
		while (close)
		{
			ft_printf("dquote>");
			get_next_line(0, (char**)argv);
			args = end_quote(args, (char*)*argv, &close);
		}
		fork_ms(args, pathes, my_env);
		if (args)
			free_tab(args);
	}
	return (0);
}
