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


int								chkpkt(int len, int nprobe)
{
	if (((struct icmp*)(g_data.rcvpacket + IPHDRLEN))->icmp_type\
			!= ICMP_TIME_EXCEEDED || len == -1)
	{
			g_data.tv_out = gettimestamp_ms();
			if (nprobe == 3 || (nprobe != 3 && ft_strcmp(g_data.oldip, g_data.ip) > 0))
				printf("%2d  %s",g_data.ttl, g_data.ip);
			if ((g_data.tv_out.tv3 - g_data.tv_in.tv3) > 0)
				printf(" %ld.%ld ms ", g_data.tv_out.tv - g_data.tv_in.tv,\
					g_data.tv_out.tv3 - g_data.tv_in.tv3);
			else if ((g_data.tv_out.tv2 - g_data.tv_in.tv2) > 0)
				printf(" %ld.%ld ms ", g_data.tv_out.tv - g_data.tv_in.tv,\
					g_data.tv_out.tv2 - g_data.tv_in.tv2);
			else
				printf(" %ld ms ", g_data.tv_out.tv - g_data.tv_in.tv);
			if (nprobe == 1 && ((struct icmp*)(g_data.rcvpacket + IPHDRLEN))->icmp_type\
				== ICMP_ECHOREPLY)
				{
					endtracer(SIGINT);
					exit (0);
				}
	}
	else
	{
		if (((struct icmp*)(g_data.rcvpacket + 48))->icmp_id != g_data.pid)
			return (0);
		else
		{
			g_data.tv_out = gettimestamp_ms();
			if (nprobe == 3 || (nprobe != 3 && ft_strcmp(g_data.oldip, g_data.ip) > 0))
				printf("%2d  %s",g_data.ttl, g_data.ip);
			if ((g_data.tv_out.tv3 - g_data.tv_in.tv3) > 0)
				printf(" %ld.%ld ms ", g_data.tv_out.tv - g_data.tv_in.tv,\
					g_data.tv_out.tv3 - g_data.tv_in.tv3);
			else if ((g_data.tv_out.tv2 - g_data.tv_in.tv2) > 0)
				printf(" %ld.%ld ms ", g_data.tv_out.tv - g_data.tv_in.tv,\
					g_data.tv_out.tv2 - g_data.tv_in.tv2);
			else
				printf(" %ld ms ", g_data.tv_out.tv - g_data.tv_in.tv);
		}	
	}
	return (1);
}
