/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putendl.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/03 11:52:45 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/01/10 20:03:42 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int	ft_putendl(char const *s)
{
	int ret;

	ret = 0;
	if (s != NULL)
		ret += ft_putendl_fd(s, 1);
	return (ret);
}
