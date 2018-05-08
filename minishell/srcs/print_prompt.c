/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_prompt.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/07 10:48:34 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/05/08 15:52:08 by volivry     ###    #+. /#+    ###.fr     */
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
	return (name);
}

void	print_prompt(int mode)
{
	char	*user;

	user = NULL;
	if (!mode)
	{
		user = get_user();
		ft_printf("\033[35m$%s> \033[0m", user);
		ft_strdel(&user);
	}
	if (mode == 1)
		ft_putstr("\033[35mquote> \033[0m");
	if (mode == 2)
		ft_putstr("\033[35mdquote> \033[0m");
	if (mode == 3)
		ft_putstr("\033[35m> \033[0m");
}
