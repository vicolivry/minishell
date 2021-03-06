/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   env_ms.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/08 11:21:15 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/05/18 16:18:06 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	env_ms2(char **args, t_list *my_env, char **pathes, t_list *arg_lst)
{
	if (args[1] && !ft_strcmp(args[1], "-i") && args[2])
	{
		lst_remove(&arg_lst, "env");
		lst_remove(&arg_lst, "-i");
		args = lst_to_tab(arg_lst);
		launch_process(args, NULL, NULL);
		free_lst(arg_lst);
		free_tab(args);
	}
	else if (args[1])
	{
		lst_remove(&arg_lst, arg_lst->content);
		args = lst_to_tab(arg_lst);
		launch_process(args, pathes, &my_env);
		free_lst(arg_lst);
		free_tab(args);
	}
	else
		free_lst(arg_lst);
}

int			env_ms(char **args, t_list *my_env, char **pathes)
{
	t_list	*tmp;
	t_list	*arg_lst;

	arg_lst = tab_to_lst(args);
	tmp = my_env;
	if (!args[1] && tmp)
	{
		while (tmp->next)
		{
			ft_printf("%s\n", tmp->content);
			tmp = tmp->next;
		}
		free_lst(arg_lst);
	}
	else if (args[1] && !ft_strcmp(args[1], "-i") && !args[2])
	{
		free_lst(arg_lst);
		return (1);
	}
	else
		env_ms2(args, my_env, pathes, arg_lst);
	return (1);
}
