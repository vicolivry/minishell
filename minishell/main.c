/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/10 13:15:55 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/04/11 19:33:35 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "minishell.h"

char	*get_user(void)
{
	uid_t			uid;
	char			*name;
	struct passwd	*pw;

	uid = getuid();
	pw = getpwuid(uid);
	name = ft_strdup(pw->pw_name);
	return (name);
}


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

int	launch_process(char **flags, char **pathes)
{
	int		i;
	int		j;
	char	**tab;
	char	*cmd;

	i = 0;
	tab = pathes;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
			j++;
		tab[i][j] = '/';
		i++;
	}
	i = 0;
	cmd = ft_strjoin(tab[i], flags[0]);
	while ((execve(cmd, flags, pathes) == -1)
			&& pathes[i])
	{
		i++;
		ft_strdel(&cmd);
		cmd = ft_strjoin(tab[i], flags[0]);
	}
	ft_strdel(&cmd);
	if (!pathes[i] && flags[0])
	{
		ft_printf("minishell: command not found: %s\n", flags[0]);
		exit(0);
	}
	return (0);
}

void	free_tab(char **tofree)
{
	int	i;

	i = 0;
	while (tofree[i])
	{

		if (tofree[i])
			free(tofree[i]);
		i++;
	}
	if (tofree)
		free(tofree);
}

int main(int argc, const char **argv, char **env)
{
	char	*usr_name;
	int		exit;
	char	**pathes;
	char	**flags;

	exit = 0;
	usr_name = get_user();
	pathes = get_pathes(env);
	flags = NULL;
	while (!exit)
	{
		ft_printf("%s>", usr_name);
		get_next_line(0, (char**)argv);
		if (!ft_strcmp((char*)*argv, "exit"))
			exit = 1;
		else
		{
			if (*argv)
				flags = ft_strsplit((char*)*argv, ' ');
			fork_ms(flags, pathes);
		}
		if (flags && ft_strcmp(argv[0], "exit"))
			free_tab(flags);
	}
	return (0);
}
