/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unpacker.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabou-h <maabou-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 11:48:38 by maabou-h          #+#    #+#             */
/*   Updated: 2020/07/13 18:54:40 by maabou-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

int						unpack(void)
{
	struct sockaddr_in	sin;
	int					ans;
	unsigned int		addr_len;
	fd_set				fds;
	struct timeval		wait;

	FD_ZERO(&fds);
	FD_SET(g_data.rsockfd, &fds);
	ans = -2;
	wait.tv_sec = g_data.opt.interval;
	wait.tv_usec = 0;
	addr_len = sizeof(struct sockaddr);
	ft_bzero(&g_data.rcvpacket, sizeof(g_data.rcvpacket));
	if (select(g_data.rsockfd+1, &fds, (fd_set*)0, (fd_set*)0, &wait) > 0)
		//ans = recvmsg(g_data.rsockfd, &msg_h, 0);
		ans = recvfrom(g_data.rsockfd, &g_data.rcvpacket, sizeof(g_data.rcvpacket), 0,  
             (struct sockaddr*)&sin, &addr_len);
	memcpy(g_data.oldip, g_data.ip, sizeof(g_data.ip));
	inet_ntop(\
		AF_INET,\
		(const void *)&((struct sockaddr_in*)&sin)->sin_addr,\
		g_data.ip,\
		sizeof(g_data.ip));
	return (ans);
}
