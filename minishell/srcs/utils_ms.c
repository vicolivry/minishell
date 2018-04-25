/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils_ms.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/20 17:40:38 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/04/25 19:05:00 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		toggle(int *close)
{
	if (!*close)
		*close = 1;
	else
		(*close = 0);
}

char		*end_quote(char *s, char *arg, int *quoted)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '"')
			toggle(quoted);
		i++;
	}
	tmp = ft_strjoin(s, arg);
	ft_strdel(&s);
	s = ft_strdup(tmp);
	ft_strdel(&tmp);
	return (s);
}

t_list	*get_env(char **env)
{
	t_list	*my_env;
	t_list	*tmp;
	int		i;

	i = 0;
	my_env = ft_lstnew(NULL, 0);
	tmp = my_env;
	while (env[i + 1])
	{
		tmp->content = ft_strdup(env[i]);
		tmp->content_size = ft_strlen(env[i]);
		tmp->next = ft_lstnew(NULL, 0);
		tmp = tmp->next;
		i++;
	}
	return (my_env);
}

char		*arr_to_str(char **arr)
{
	int		i;
	int		j;
	int		k;
	int		len;
	char	*str;

	i = -1;
	k = 0;
	len = 0;
	str = NULL;
	while (arr[++i])
		len += ft_strlen(arr[i]);
	if (!(str = malloc(len + 1)))
		return (NULL);
	i = 0;
	while (arr[i])
	{
		j = 0;
		while (arr[i][j])
			str[k++] = arr[i][j++];
		i++;
	}
	str[k] = 0;
	return (str);
}

char		**split_nulls(char *s, int len)
{
	char	**args;
	int		count;
	int		i;
	int		j;

	args = NULL;
	i = 0;
	j = 0;
	count = ft_wordcount_ms(s, len);
	if (!s || !(args = (char **)malloc(sizeof(char*) * (count + 1))))
		return (NULL);
	while (i <= len)
	{
		if (s[i])
		{
			args[j] = ft_strsub(s, i, ft_strlen(s + i));
			i += ft_strlen(s + i) + 1;
			*s = *s + i;
			j++;
		}
		else
			i++;
	}
	args[j] = NULL;
	return (args);
}
