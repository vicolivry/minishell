/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fork_ms.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/11 13:14:12 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/04/20 16:00:32 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			fork_ms(char **args, char **pathes, t_list *my_env)
{
	pid_t	pid;

	if (builtin_ms(my_env, args) == 1)
		return (0);
	pid = fork();
	if (pid == -1) //ERROR
		return (-1);
	else if (pid == 0) //In the Child process
		launch_process(args, pathes);
	else if (pid > 0) // In the Parent process
		wait(NULL);
	return (0);
}
