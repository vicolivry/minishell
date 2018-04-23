/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   process.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/17 11:00:04 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/04/23 18:41:17 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	*get_env(char **env)
{
	t_list	*my_env;
	t_list	*tmp;
	int		i;

	i = 0;
	my_env = ft_lstnew(NULL, 0);
	tmp = my_env;
	while (env[i + 1])
	{
		tmp->content = ft_strdup(env[i]);
		tmp->content_size = ft_strlen(env[i]);
		tmp->next = ft_lstnew(NULL, 0);
		tmp = tmp->next;
		i++;
	}
	return (my_env);
}

int		launch_process(char **args, char **pathes)
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
	cmd = ft_strjoin(tab[i], args[0]);
	while ((execve(cmd, args, pathes) == -1) && pathes[i])
	{
		i++;
		cmd = ft_strjoin(tab[i], args[0]);
	}
	if (!pathes[i] && args[0])
	{
		ft_printf("minishell: command not found: %s\n", args[0]);
		exit(0);
	}
	return (0);
}
