/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabou-h <maabou-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 11:48:38 by maabou-h          #+#    #+#             */
/*   Updated: 2019/08/20 15:47:29 by maabou-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void		ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*d;

	i = 0;
	d = (char*)s;
	while (i < n)
	{
		d[i] = 0;
		i++;
	}
}

int			ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int			ft_atoi(const char *str)
{
	int		i;
	int		neg;
	long	ret;

	i = 0;
	ret = 0;
	neg = 0;
	if (!str || !*str)
		return (0);
	while (str[i] && ((str[i] >= 7 && str[i] <= 13 && str[i] != '\n')
			|| str[i] == ' '))
		i++;
	if (str[i] && str[i] == '-')
		neg = 1;
	if (str[i] && (str[i] == '+' || str[i] == '-'))
		i++;
	while (str[i] && str[i] <= '9' && str[i] >= '0')
	{
		ret *= 10;
		ret += str[i++] - '0';
	}
	if ((str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122))
		return (-1);
	return ((neg) ? ((int)-ret) : ((int)ret));
}

t_tval				gettimestamp_ms(void)
{
	struct timeval	te;
    t_tval          tv;
	long			mm;

	gettimeofday(&te, NULL);
    ft_bzero(&tv, sizeof(t_tval));
	tv.tv = te.tv_sec * 1000LL + te.tv_usec / 1000;
	mm = te.tv_sec * 10LL + te.tv_usec / 10;
	tv.tv3 = mm % 1000;
    tv.tv2 = mm % 100;
    return (tv);
}