/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabou-h <maabou-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 11:48:38 by maabou-h          #+#    #+#             */
/*   Updated: 2019/08/20 15:47:29 by maabou-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void		tracer(void)
{
	ssize_t	responsesize;
	int		nprobes;
	
	responsesize = 0;
	nprobes = 4;
	while (--nprobes)
	{
		pack();
		g_data.tv_in = gettimestamp_ms();
		if (sendto(g_data.sockfd, g_data.packet, DATALEN + ICMPHDRLEN\
					+ IPHDRLEN, 0, g_data.info->ai_addr,\
					g_data.info->ai_addrlen) < 0)
		{
			printf("closing fd\n");
			close(g_data.sockfd);
			exit(1);
		}
		while((responsesize = unpack()))
			chkpkt(responsesize, nprobes);
	}
	printf("\n");
}

int			main(int argc, char **argv)
{
	int		v;
	int		i;

	i = 64;
	ft_bzero(&g_data, sizeof(g_data));
	g_data.pid = getpid();
	g_data.seq = 0;
	g_data.ttl = 0;
	if ((v = options(argc, argv + 1)) < 1)
	{
		printf("Usage: ft_traceroute [-h] [-i interval] [-t ttl] destination\n");
		exit(0);
	}
	initprog();
	printf("ft_traceroute to %s (%s), %d hops max, 60 bytes packets\n", g_data.dest, g_data.ip, i);
	while (--i)
	{
		tracer();
		g_data.ttl++;
	}
	return (0);
}
