/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free_ms.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/12 14:28:03 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/05/16 16:26:53 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	free_tab(char **tofree)
{
	int	i;

	i = 0;
	while (tofree[i])
	{
		if (tofree[i] != 0)
			ft_strdel(&tofree[i]);
		i++;
	}
	if (tofree)
		free(tofree);
}
