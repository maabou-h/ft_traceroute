/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabou-h <maabou-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 11:48:38 by maabou-h          #+#    #+#             */
/*   Updated: 2019/08/20 15:47:29 by maabou-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static void				initaddressdata(void)
{
	struct addrinfo	hints;

	ft_bzero(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_RAW;
	hints.ai_protocol = IPPROTO_ICMP;
	if (getaddrinfo(g_data.dest, NULL, &hints, &g_data.info))
	{
		dprintf(2, "ft_traceroute: %s: Name or service not known\n", g_data.dest);
		exit(1);
	}
}

static void				initsocket(void)
{
	struct timeval tv= {g_data.opt.timeo,0};

	if ((g_data.sockfd = socket(AF_INET,\
					SOCK_RAW, IPPROTO_ICMP)) < 0)
	{
		dprintf(2, "ft_traceroute: error creating socket\n");
		exit(1);
	}
	if (setsockopt(g_data.sockfd, IPPROTO_IP, IP_HDRINCL,\
				(int[1]){1}, sizeof(int)) < 0)
	{
		close(g_data.sockfd);
		exit(1);
	}
	if (setsockopt(g_data.sockfd, SOL_SOCKET, SO_RCVTIMEO,\
				&tv, sizeof(struct timeval)) < 0)
	{
		close(g_data.sockfd);
		exit(1);
	}
	if ((g_data.rsockfd = socket(AF_INET,\
					SOCK_RAW, IPPROTO_ICMP)) < 0)
	{
		dprintf(2, "ft_traceroute: error creating socket\n");
		exit(1);
	}
	if (setsockopt(g_data.rsockfd, IPPROTO_IP, IP_HDRINCL,\
				(int[1]){1}, sizeof(int)) < 0)
	{
		close(g_data.rsockfd);
		exit(1);
	}
	if (setsockopt(g_data.rsockfd, SOL_SOCKET, SO_RCVTIMEO,\
				&tv, sizeof(struct timeval)) < 0)
	{
		close(g_data.rsockfd);
		exit(1);
	}
}

void				initprog(void)
{
	if (getuid() != 0)
	{
		dprintf(2, "ft_traceroute: must run as root\n");
		exit(1);
	}
	initaddressdata();
	initsocket();
	ft_bzero(&g_data.ip, sizeof(g_data.ip));
	ft_bzero(&g_data.oldip, sizeof(g_data.oldip));
	inet_ntop(AF_INET,\
			&((const struct sockaddr_in*)g_data.info->ai_addr)->sin_addr,\
			g_data.ip,\
			sizeof(g_data.ip));
}