/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   dollar_conv.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/16 12:10:56 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/05/16 18:13:54 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*con_env(int j, t_list *my_env, char *s)
{
	t_list	*tmp;
	char	*word;
	char	**tab;

	tmp = my_env;
	tab = NULL;
	word = NULL;
	tab = ft_strsplit(s, '$');
	ft_printf("quoted s: %s\n", s);
		ft_printf("tab[0] : %s\n", tab[0]);
		ft_printf("tab[j] : %s\n", tab[1]);
	ft_strdel(&s);
	while (tab[j])
	{

		if (!(word = get_env_value(tab[j], my_env)))
			word = NULL;
		ft_strdel(&tab[j]);
		tab[j] = ft_strdup(word);
		ft_strdel(&word);
		j++;
	}
	s = arr_to_str(tab);
	free_tab(tab);
	return (s);
}

static char	*find_dollar(char *s, t_list *my_env)
{
	int		i;
	char	**tab;

	i = 0;
	tab = NULL;

	if (s && i == 0 && s[i] == '$')
		return (con_env(0, my_env, s));
	else if (s && ft_strchr(s, '$'))
	{
		return (con_env(1, my_env, s));
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
	s = NULL;
	while (tab && tab[i])
	{

		tab[i] = find_dollar(tab[i], my_env);
		s = str_append(s, tab[i]);


		if (tab[i + 1])
			s = str_append(s, " ");
		i++;
	}
	s[ft_strlen(s)] = 0;
	free_tab(tab);

	if (!s[0])
		return (NULL);
	return (s);
}
