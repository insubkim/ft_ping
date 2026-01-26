/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 18:06:04 by insub             #+#    #+#             */
/*   Updated: 2026/01/26 03:08:26 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

#include "raw_socket.h"
#include "icmp.h"
#include "ping.h"
#include "signal_handler.h"

#define BUFFER_SIZE 1024

int g_summary_flag = 0;

int	main(int argc, char **argv)
{
	int		sockfd;
	char	reply_buffer[BUFFER_SIZE] = {0, };
	int		length;
	char	*ip_addr;
	t_ping_stats ping_stats = {0, };

	if (argc != 2)
	{
		printf(PING_USAGE);
		return (1);
	}
	
	ip_addr = hostname_to_ipv4_addr(argv[1]);
	if (ip_addr == NULL)
	{
		printf("ping: %s: Name or service not know\n", argv[1]);
		return (1);
	}
	
	printf("PING %s (%s) 56(84) data bytes\n", argv[1], ip_addr);
	
	sockfd = create_icmp_socket();
	if (sockfd < 0)
	{
		printf("Failed to create raw socket\n");
		return (1);
	}
	
	if (set_socket_timeout(sockfd, 5) < 0)
	{
		close(sockfd);
		return (1);
	}

	set_signal();

	 while (g_summary_flag == 0)
	 {
	    unsigned int    ping_start_time_micro;
		ping_start_time_micro = get_current_time_micro();

		if (send_icmp_echo_request(sockfd, ip_addr) < 0)
		{
			close(sockfd);
			return (1);
		}
		
		length = receive_icmp_echo_reply(sockfd, reply_buffer, BUFFER_SIZE);
		if (length < 0)
		{
			close(sockfd);
			return (1);
		}
		
		process_icmp_reply(reply_buffer, length, &ping_stats, ping_start_time_micro);
		sleep(1);
	}

	print_ping_summary(ping_stats, argv[1]);
	
	close(sockfd);
	return (0);
}