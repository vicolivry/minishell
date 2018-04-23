/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fork_ms.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/11 13:14:12 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/04/23 18:06:18 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			fork_ms(char **args, char **pathes, t_list *my_env)
{
	pid_t	pid;

	pid = 0;
	if (builtin_ms(my_env, args, pathes) == 1)
		return (0);
	pid = fork();
	if (pid == -1)
		return (-1);
	else if (pid == 0)
		launch_process(args, pathes);
	else if (pid > 0)
		wait(NULL);
	return (0);
}
