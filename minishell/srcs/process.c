/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   process.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/17 11:00:04 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/04/25 13:50:08 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		launch_process(char **args, char **pathes, t_list *my_env)
{
	int				i;
	char			*cmd;
	struct dirent	*dp;
	DIR				*dirp;

	i = 0;
	cmd = NULL;
	if (builtin_ms(my_env, args, pathes) == 1)
		return (0);
	while (pathes[i])
	{
		if ((dirp = opendir(pathes[i])) != NULL)
		{
			while ((dp = readdir(dirp)) != NULL)
				if (!(ft_strcmp(args[0], dp->d_name)))
				{
					cmd = ft_strjoin(pathes[i], args[0]);
					fork_ms(cmd, args);
					return (0);
				}
		}
		closedir(dirp);
		i++;
	}
	ft_printf("minishell: command not found: %s\n", args[0]);
	return (0);
}
