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

#include "ft_ping.h"

int						unpack(void)
{
	struct msghdr		msg_h;
	struct sockaddr_in	sin;
	struct iovec		iov[1];
	int					ans;
	fd_set fds;
	struct timeval wait;

	FD_ZERO(&fds);
	FD_SET(g_data.rsockfd, &fds);
	wait.tv_sec = 5;
	wait.tv_usec = 0;
	ft_bzero(&g_data.rcvpacket, sizeof(g_data.rcvpacket));
	ft_bzero(&msg_h, sizeof(msg_h));
	ft_bzero(&sin, sizeof(sin));
	ft_bzero(&iov, sizeof(iov));
	iov[0].iov_base = g_data.rcvpacket;
	iov[0].iov_len = sizeof(g_data.rcvpacket);
	msg_h.msg_name = &sin;
	msg_h.msg_namelen = sizeof(sin);
	msg_h.msg_control = 0;
	msg_h.msg_controllen = 0;
	msg_h.msg_iov = iov;
	msg_h.msg_iovlen = 1;
	msg_h.msg_flags = 0;
	if (select(g_data.rsockfd+1, &fds, (fd_set *)0, (fd_set *)0, &wait) > 0)
		ans = recvmsg(g_data.rsockfd, &msg_h, 0);
	inet_ntop(\
		AF_INET,\
		(const void *)&((struct sockaddr_in*)&sin)->sin_addr,\
		g_data.ip,\
		sizeof(g_data.ip));
	return (ans);
}
