/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   process.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/02 11:42:21 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/05/02 15:29:17 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	verif_path(struct dirent *dp, char **pathes, char **args, int i)
{
	char	*cmd;

	cmd = NULL;
	if (!(ft_strcmp(args[0], dp->d_name)))
	{
		cmd = ft_strjoin(pathes[i], args[0]);
		if (access(cmd, X_OK) == -1)
		{
			ft_printf("minishell: permission denied: %s\n", args[0]);
			ft_strdel(&cmd);
			return (1);
		}
		fork_ms(cmd, args);
		return (1);
	}
	return (0);
}

int			launch_process(char **args, char **pathes, t_list *my_env)
{
	struct dirent	*dp;
	DIR				*dirp;
	int				i;

	i = 0;
	if (builtin_ms(my_env, args, pathes) == 1)
		return (0);
	while (pathes[i])
	{
		if ((dirp = opendir(pathes[i])) != NULL)
			while ((dp = readdir(dirp)) != NULL)
				if (verif_path(dp, pathes, args, i))
				{
					closedir(dirp);
					return (0);
				}
		closedir(dirp);
		i++;
	}
	ft_printf("minishell: command not found: %s\n", args[0]);
	return (0);
}
