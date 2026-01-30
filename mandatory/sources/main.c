/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 18:06:04 by insub             #+#    #+#             */
/*   Updated: 2026/01/26 05:32:29 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <getopt.h>

#include "raw_socket.h"
#include "icmp.h"
#include "ping.h"
#include "signal_handler.h"

#define BUFFER_SIZE 1024

int g_summary_flag = 0;
t_ping_options	g_options = {0};

static int	parse_options(int argc, char **argv)
{
	int	opt;

	while ((opt = getopt(argc, argv, "v?")) != -1)
	{
		if (opt == 'v')
			g_options.verbose = 1;
		else if (opt == '?')
		{
			return (-1);
		}
	}

	if ((g_options.verbose && argc < 3) 
		|| (!g_options.verbose && argc < 2))
		return (-1);

	return (optind);
}

int	main(int argc, char **argv)
{
	int		sockfd;
	char	reply_buffer[BUFFER_SIZE] = {0, };
	int		length;
	char	*ip_addr;
	t_ping_stats ping_stats = {0, };
	int		arg_index;

	arg_index = parse_options(argc, argv);
	if (arg_index < 0)
	{
		printf(PING_HELP);
		return (0);
	}

	sockfd = create_icmp_socket();
	if (sockfd < 0)
	{
		printf("Failed to create raw socket\n");
		return (1);
	}

	if (g_options.verbose)
		printf("ping: sock4.fd: %d (socktype: SOCK_RAW), hints.ai_family: AF_INET\n\n", sockfd);

	ip_addr = hostname_to_ipv4_addr(argv[arg_index]);
	if (ip_addr == NULL)
	{
		printf("ping: %s: Name or service not know\n", argv[arg_index]);
		close(sockfd);
		return (1);
	}

	if (g_options.verbose)
		printf("ai->ai_family: AF_INET, ai->ai_canonname: '%s'\n", argv[arg_index]);

	printf("PING %s (%s) 56(84) data bytes\n", argv[arg_index], ip_addr);
	
	if (set_socket_timeout(sockfd, 5) < 0)
	{
		close(sockfd);
		return (1);
	}

	set_signal();

	while (g_summary_flag == 0)
	{
		int64_t	ping_start_time_micro;
		int		reply_received;

		ping_start_time_micro = get_current_time_micro();

		if (send_icmp_echo_request(sockfd, ip_addr) < 0)
		{
			close(sockfd);
			return (1);
		}

		reply_received = 0;
		while (reply_received == 0 && g_summary_flag == 0)
		{
			length = receive_icmp_echo_reply(sockfd, reply_buffer, BUFFER_SIZE);
			if (length < 0)
			{
				ping_stats.packets_sent++;
				ping_stats.packets_lost++;
				if (ping_stats.ping_start_time_ms == 0)
					ping_stats.ping_start_time_ms = ping_start_time_micro / 1000;
				break ;
			}
			reply_received = process_icmp_reply(reply_buffer, length,
					&ping_stats, ping_start_time_micro);
		}
		sleep(1);
	}

	print_ping_summary(ping_stats, argv[arg_index]);
	
	close(sockfd);
	return (0);
}