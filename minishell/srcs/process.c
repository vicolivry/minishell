/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   process.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/17 11:00:04 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/04/19 17:49:00 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**get_env(char **env)
{
	char	**my_env;
	int		i;

	i = 0;
	while (env[i])
		i++;
	if (!(my_env = (char**)malloc(sizeof(char*) * i)))
		return (NULL);
	i = 0;
	while (env[i + 1])
	{
		my_env[i] = ft_strdup(env[i]);
		i++;
	}
	my_env[i] = NULL;
	return (my_env);
}

int	launch_process(char **args, char **pathes, char **env)
{
	int		i;
	int		j;
	char	**tab;
	char	*cmd;

	i = 0;
	tab = pathes;
	builtin_ms(env, args);
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
			j++;
		tab[i][j] = '/';
		i++;
	}
	i = 0;
	cmd = ft_strjoin(tab[i], args[0]);

	while ((execve(cmd, args, pathes) == -1)
			&& pathes[i])
	{
		i++;
//		ft_strdel(&cmd);
		cmd = ft_strjoin(tab[i], args[0]);
	}
//	ft_strdel(&cmd);
	if (!pathes[i] && args[0])
	{
		ft_printf("minishell: command not found: %s\n", args[0]);
		exit(0);
	}
	return (0);
}
