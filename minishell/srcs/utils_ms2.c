/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils_ms2.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/09 13:14:18 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/05/18 17:51:28 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	ft_wordcount_ms(char *s, int len)
{
	size_t	res;
	int		i;

	i = 0;
	res = 0;
	while (i <= len)
	{
		if (i > 0 && !s[i] && s[i - 1])
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
	while (tmp->content && !ft_strstr(tmp->content, key))
		tmp = tmp->next;
	if (tmp->content)
		temp = ft_strchr(tmp->content, '=') + 1;
	value = ft_strdup(temp);
	if (!value)
		return (NULL);
	return (value);
}

char	**get_pathes(t_list *my_env)
{
	t_list	*tmp;
	char	*str;
	char	**pathes;
	int		i;

	tmp = my_env;
	str = NULL;
	pathes = NULL;
	if (!tmp)
		return (NULL);
	while (!ft_strstr(tmp->content, "PATH") && tmp->next)
		tmp = tmp->next;
	if (!tmp->content)
		return (NULL);
	str = ft_strchr(tmp->content, '=') + 1;
	pathes = ft_strsplit(str, ':');
	i = 0;
	while (pathes[i])
	{
		pathes[i] = str_append(pathes[i], "/");
		i++;
	}
	return (pathes);
}
