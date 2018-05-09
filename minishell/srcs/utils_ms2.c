/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils_ms2.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/09 13:14:18 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/05/09 17:41:17 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	ft_wordcount_ms(char *s, int len)
{
	size_t	res;
	int		i;

	i = 1;
	res = 0;
	while (i <= len)
	{
		if (!s[i] && s[i - 1])
			res++;
		i++;
	}
	return (res);
}

void	lst_remove(t_list **lst, char *str)
{
	t_list	*tmp;
	t_list	*prev;

	tmp = *lst;
	if (tmp && ft_strstr(tmp->content, str))
	{
		*lst = tmp->next;
		ft_memdel((void**)&tmp->content);
		free(tmp);
		return ;
	}
	while (tmp && !ft_strstr(tmp->content, str))
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
		return ;
	prev->next = tmp->next;
	ft_memdel((void**)&tmp->content);
	free(tmp);
}

char	*get_env_value(char *key, t_list *my_env)
{
	t_list	*tmp;
	char	*temp;
	char	*value;

	temp = NULL;
	value = NULL;
	tmp = my_env;
	if (!tmp)
		tmp = ft_lstnew(NULL, 0);
	while (!ft_strstr(tmp->content, key))
		tmp = tmp->next;
	temp = ft_strchr(tmp->content, '=') + 1;
	value = ft_strdup(temp);
	return (value);
}


