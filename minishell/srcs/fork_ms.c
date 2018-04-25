/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fork_ms.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/11 13:14:12 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/04/25 14:10:06 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			fork_ms(char *cmd, char **args)
{
	pid_t	pid;

	pid = 0;
	pid = fork();
	if (pid == -1)
		return (-1);
	else if (pid == 0)
		execve(cmd, args, NULL);
	else if (pid > 0)
	{
		wait(NULL);
		ft_strdel(&cmd);
	}
	return (0);
}
