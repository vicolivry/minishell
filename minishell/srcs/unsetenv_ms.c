/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   unsetenv_ms.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/08 11:22:01 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/05/09 13:14:04 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	unsetenv_ms(char **args, t_list **my_env)
{
	char	*str;

	if (!args[1])
		ft_putendl("unsetenv: too few arguments (expected one)");
	if (args[1] && !args[2])
	{
		str = ft_strjoin(args[1], "=");
		lst_remove(my_env, str);
		ft_strdel(&str);
	}
	if (args[1] && args[2])
		ft_putendl("unsetenv : too many arguments (expected one)");
	return (1);
}
