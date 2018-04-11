/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_wordcount.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: volivry <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/03 12:06:48 by volivry      #+#   ##    ##    #+#       */
/*   Updated: 2018/04/11 19:00:57 by volivry     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_wordcount(const char *s, char c)
{
	size_t	result;
	int		i;

	result = 0;
	i = 0;
	while (s[i])
	{
		if ((i == 0 && s[i] != c) || (i > 1 && (s[i] != c && s[i - 1] == c)))
			result++;
		i++;
	}
	return (result);
}
