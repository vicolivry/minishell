/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   process.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/02 11:42:21 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/05/18 17:50:57 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <sys/types.h>
#include <sys/stat.h>

static int	verif_path(struct dirent *dp, char **pathes, char **args, int i)
{
	char	*cmd;

	cmd = NULL;
	if (args)
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
			ft_strdel(&cmd);
			return (1);
		}
	return (0);
}

static int	abs_path(char *s, char **args)
{
	if (!(access(s, X_OK)) && ft_strcmp(args[0], "minishell"))
	{
		fork_ms(s, args);
		return (1);
	}
	return (0);
}

static int	browse_pathes(char **pathes, char **args)
{
	struct dirent	*dp;
	DIR				*dirp;
	int				i;

	i = 0;
	while (pathes[i])
	{
		if ((dirp = opendir(pathes[i])) != NULL)
			while ((dp = readdir(dirp)) != NULL)
				if (verif_path(dp, pathes, args, i))
				{
					closedir(dirp);
					return (1);
				}
		closedir(dirp);
		i++;
	}
	return (0);
}

static void	cmd_err(char **args, DIR *dirp)
{
	if ((dirp = opendir(args[0])))
	{
		ft_printf("minishell: %s is a directory\n", args[0]);
		closedir(dirp);
	}
	else
		ft_printf("minishell: command not found: %s\n", args[0]);
}

int			launch_process(char **args, char **pathes, t_list **my_env)
{
	DIR				*dirp;

	if (args && ft_strcmp(args[0], "./minishell"))
	{
		if (builtin_ms(my_env, args, pathes) == 1)
			return (0);
		if (args)
		{
			if (!(dirp = opendir(args[0])))
			{
				if ((abs_path(args[0], args)))
					return (0);
			}
			else
				closedir(dirp);
		}
		if (pathes)
			if (browse_pathes(pathes, args))
				return (0);
		cmd_err(args, dirp);
	}
	return (0);
}
