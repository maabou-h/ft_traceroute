/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timestamp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabou-h <maabou-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 11:48:38 by maabou-h          #+#    #+#             */
/*   Updated: 2019/08/20 15:47:29 by maabou-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

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