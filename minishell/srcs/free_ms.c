/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free_ms.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/12 14:28:03 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/05/08 12:05:21 by volivry     ###    #+. /#+    ###.fr     */
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

void	free_lst(t_list *lst)
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp = lst;
	while (tmp)
	{
		tmp2 = tmp->next;
		ft_memdel((void**)&tmp->content);
		ft_memdel((void**)&tmp);
		tmp = tmp2;
	}
}
