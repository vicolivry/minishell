/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   dollar_conv.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/15 17:52:43 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/05/15 19:00:30 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"


static char	*sub_word(int i, int j, t_list *my_env, char *str1, char *s)
{
	char	*word;
	t_list	*tmp;
	int		k;
	char	*value;

	tmp = my_env;
	word = NULL;
	value = NULL;
	if (!(word = (char*)malloc(sizeof(char) * (j - i + 1))))
		return (NULL);
	k = 0;
	while (i <= j)
	{
		word[k++] = s[i];
		i++;
	}
	if (!(value = get_env_value(word, my_env)))
		value = NULL;
	str1 = str_append(str1, value);
	while (str1[i])
		i++;
	str1 = str_append(str1, word);
	ft_strdel(&s);
	s = ft_strdup(str1);
	ft_strdel(&str1);
	return (s);
}

static char	*find_dollar(char *s, t_list *my_env)
{
	int		i;
	int		j;
	char	*str1;

	i = 0;
	str1 = NULL;
	while (s && s[i])
	{
		if (i == 0 && s[i] == '$')
		{
			i++;
			s = sub_word(i, j, my_env, str1, s);
		}
		else if (s > 0 && s[i] == '$')
		{
			if (!(str1 = (char*)malloc(sizeof(char) * (i + 1))))
				return (NULL);
			j = 0;
			while (j < i)
			{
				str1[j] = s[j];
				j++;
			}
			str1[j] = 0;
			i++;
			ft_printf("str1 = %s\n", str1);
			s = sub_word(i, j, my_env, str1, s);
		}
		i++;
	}
	return (s);
}

char		*dollar_conv(char *s, t_list *my_env)
{
	char	**tab;
	int		i;

	tab = NULL;
	i = 0;
	tab = ft_strsplit(s, ' ');
	ft_strdel(&s);
	while (tab && tab[i])
	{
		tab[i] = find_dollar(tab[i], my_env);
		s = str_append(s, tab[i]);
		if (tab[i + 1])
			s = str_append(s, " ");
		ft_printf("tab[i] : [%s]\n", tab[i]);
		i++;
	}
	s[ft_strlen(s) + 1] = 0;
	free_tab(tab);
	ft_printf("end of $ conv S = %s\n", s);
	return (s);
}
