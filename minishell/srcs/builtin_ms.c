/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_ms.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/19 17:24:10 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/04/19 17:50:18 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void env_ms(char **my_env)
{
	int	i;

	i = 0;
	while (my_env[i + 1])
	{
		ft_printf("%s\n", my_env[i]);
		i++;
	}
}

static void echo_ms(char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		ft_printf("%s", args[i]);
		i++;
	}
	ft_putchar('\n');
}

void	builtin_ms(char **env, char **args)
{
	char	**my_env;

	my_env = get_env(env);
	if (!ft_strcmp(args[0], "env"))
		env_ms(my_env);
	if (!ft_strcmp(args[0], "echo"))
		echo_ms(args);
	exit(0);
}
