/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ls.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/07 15:21:13 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/04/19 17:49:31 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <pwd.h>
# include <signal.h>

int		fork_ms(char **args, char **pathes, char **env);
int		launch_process(char **args, char **pathes, char **env);
void	free_tab(char **tofree);
char	**get_args(char *s, int *close);
char	**end_quote(char **args, char *s, int *close);
char	**get_env(char **env);
void	builtin_ms(char **env, char **args);
#endif
