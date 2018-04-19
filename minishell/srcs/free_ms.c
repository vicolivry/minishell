/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free_ms.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/12 14:28:03 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/04/12 15:06:41 by volivry     ###    #+. /#+    ###.fr     */
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

		if (tofree[i])
			free(tofree[i]);
		i++;
	}
	if (tofree)
		free(tofree);
}
