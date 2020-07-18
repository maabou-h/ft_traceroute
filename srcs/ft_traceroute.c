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

void	endtracer(int sig)
{
	(void)sig;
	printf("\n");
	close(g_data.sockfd);
	close(g_data.rsockfd);
	exit(1);
}

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
			close(g_data.sockfd);
			exit(1);
		}
	}
	nprobes = 4;
	while (--nprobes)
	{
		responsesize = unpack();
		if (responsesize < 1)
		{
			if (nprobes == 3)
				printf("%2d  ", g_data.ttl);
			printf("* ");

		}
		else
			chkpkt(responsesize, nprobes);
	}
	printf("\n");
}

int			main(int argc, char **argv)
{
	int		v;
	int		i;

	i = -1;
	signal(SIGINT, endtracer);
	ft_bzero(&g_data, sizeof(g_data));
	g_data.pid = getpid();
	g_data.seq = 0;
	g_data.ttl = 1;
	if ((v = options(argc, argv + 1)) < 1)
	{
		dprintf(2, "Usage: ft_traceroute [-h] [-i waitinterval] [-I ttl interval] [-T timeout] [-H hoplimit] destination\n");
		exit(0);
	}
	initprog();
	dprintf(1, "ft_traceroute to %s (%s), %d hops max, 60 byte packets\n", g_data.dest, g_data.ip, g_data.opt.hlim);
	while (++i < g_data.opt.hlim)
	{
		tracer();
		g_data.ttl += g_data.opt.ttlint;
	}
	return (0);
}
