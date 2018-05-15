/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ls.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/07 15:21:13 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/05/15 15:59:51 by volivry     ###    #+. /#+    ###.fr     */
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
# include <dirent.h>

# define BCK_SLASHES "sbtnrv\\"

int		fork_ms(char *cmd, char **args);
int		launch_process(char **args, char **pathes, t_list **my_env);
void	free_tab(char **tofree);
char	**get_args(char *s, char **args, t_list *my_env);
char	*end_quote(char *s, char *arg, int *quoted);
t_list	*get_env(char **env);
int		builtin_ms(t_list **my_env, char **args, char **pathes);
void	single_toggle(int *close);
void	double_toggle(int *close);
char	*arr_to_str(char **arr);
char	**split_nulls(char *s, int len);
size_t	ft_wordcount_ms(char *s, int len);
char	*trim_double_quote(char *arg, int *quoted, int len);
char	*trim_single_quote(char *arg, int *quoted, int len);
char	*conv_str(char *s, int *quoted, char **args);
void	toggle_ms(int *quoted, int i, char *s);
char	*back_slashes_echo(char *s, int i);
void	toggling(char *s, int *quoted, int len);
char	*slashed_arg(char *s, size_t len, char **argv, int *quoted);
char	*quoted_arg(char *s, size_t len, char **argv, int *quoted);
char	**multi_cmd(char *s, char **argv);
void	print_prompt(int mode);
int		cd_ms(char **args, t_list **my_env);
int		setenv_ms(char **args, t_list **my_env);
int		unsetenv_ms(char **args, t_list **my_env);
int		env_ms(char **args, t_list *my_env, char **pathes);
void	free_lst(t_list *lst);
void	lst_remove(t_list **lst, char *str);
char	*get_user(void);
char	*dollar_conv(char *s, t_list *my_env);
char	*get_env_value(char *key, t_list *my_env);

#endif
