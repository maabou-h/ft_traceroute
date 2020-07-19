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

#ifndef FT_TRACEROUTE_H
# define FT_TRACEROUTE_H
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
# define MAXHOPS		30

typedef struct			s_opt
{
	int					interval;
	int					hlim;
	int					timeo;
	int					ttlint;
	int					nopt;
}						t_opt;


typedef struct			s_tval
{
	long				tv3;
	long				tv2;
	long				tv;
}						t_tval;

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
	char				oldip[INET_ADDRSTRLEN];
	char				addr[INET_ADDRSTRLEN];
	t_opt				opt;
	t_tval				tv_in;
	t_tval				tv_out;
	struct addrinfo		*info;
}						t_data;

t_data					g_data;

void					endtracert(int sig);

void					pack(void);
int						unpack(void);

void					sockaddr_io(void);

int						options(int argc, char **av);

int						checkprobe(int len, int nprobe);

void					ft_bzero(void *s, size_t n);
int						ft_atoi(const char *str);
int						ft_strcmp(const char *s1, const char *s2);
t_tval					gettimestamp_ms(void);

#endif
