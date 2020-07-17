/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabou-h <maabou-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 11:48:38 by maabou-h          #+#    #+#             */
/*   Updated: 2019/08/20 15:47:29 by maabou-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
# define FT_PING_H
# include <stdio.h>
# include <signal.h>
# include <arpa/inet.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <netinet/in.h>
# include <netinet/ip_icmp.h>
# include <netdb.h>
# include <string.h>
# define ICMPPAYLOAD	1472
# define ICMPHDRLEN		8
# define DATALEN		56
# define IPHDRLEN		20
# define STDTTL			255
# define PKTLEN			84

typedef struct			s_opt
{
	int					verbose;
	int					interval;
	int					ttl;
	int					nopt;
}						t_opt;

typedef struct			s_data
{
	int					sockfd;
	int					rsockfd;
	int					seq;
	int					ttl;
	pid_t				pid;
	char				*dest;
	char				packet[ICMPPAYLOAD];
	char				rcvpacket[ICMPPAYLOAD];
	char				ip[INET_ADDRSTRLEN];
	char				addr[INET_ADDRSTRLEN];
	t_opt				opt;
	struct addrinfo		*info;
}						t_data;

t_data					g_data;

unsigned short			calculatechecksum(unsigned short *addr, int len);
void					pack(void);
int						unpack(void);
void					initprog(void);
int						options(int argc, char **av);
int						chkpkt(int len);
long					gettimestamp_ms(int flag);
void					ft_bzero(void *s, size_t n);
int						ft_atoi(const char *str);
int						ft_strcmp(const char *s1, const char *s2);

#endif
