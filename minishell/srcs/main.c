/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/10 13:15:55 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/04/20 16:01:10 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_user(void)
{
	uid_t			uid;
	char			*name;
	struct passwd	*pw;

	uid = getuid();
	pw = getpwuid(uid);
	name = ft_strdup(pw->pw_name);
	//	free(pw);
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

int main(int argc, const char **argv, char **env)
{
	char	*usr_name;
	char	**pathes;
	char	**args;
	t_list	*my_env;
	int		close;

	close = 0;
	my_env = get_env(env);
	usr_name = get_user();
	pathes = get_pathes(env);
	args = NULL;
	while (101)
	{
		ft_printf("%s>", usr_name);
		get_next_line(0, (char**)argv);
		if (*argv)
			args = get_args((char*)*argv, &close);
		while (close)
		{
			ft_printf("dquote>");
			get_next_line(0, (char**)argv);
			args = end_quote(args, (char*)*argv, &close);
		}
		if (!ft_strcmp(argv[0], "exit"))
				exit(0);
		fork_ms(args, pathes, my_env);
		/*	if (args && ft_strcmp(argv[0], "exit"))
			free_tab(args);
			free((void*)*argv);*/
	}
	ft_strdel(&usr_name);
	return (0);
}
