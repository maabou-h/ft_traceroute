/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabou-h <maabou-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 11:48:38 by maabou-h          #+#    #+#             */
/*   Updated: 2020/07/13 18:55:34 by maabou-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static void						badpacket(struct icmp *icmp)
{
	if (icmp->icmp_id != g_data.pid)
		return ;
	else
	{
		printf(" %s ",\
				g_data.ip);
	}
}

int								chkpkt(int len)
{
	if (((struct icmp*)(g_data.rcvpacket + IPHDRLEN))->icmp_type\
			== ICMP_ECHOREPLY || len == -1)
	{
			return (0);
	}
	else
		badpacket((struct icmp*)(g_data.rcvpacket + 48));
	return (1);
}
