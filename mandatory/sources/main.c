/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: insub <insub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 18:06:04 by insub             #+#    #+#             */
/*   Updated: 2026/01/19 19:31:45 by insub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

#include "raw_socket.h"
#include "icmp.h"

#define BUFFER_SIZE 1024

int	main(int argc, char **argv)
{
	int		sockfd;
	char	reply_buffer[BUFFER_SIZE];
	int		length;

	if (argc != 2)
	{
		printf("Usage: %s <IP_ADDRESS>\n", argv[0]);
		return (1);
	}
	printf("Ping Start\n");
	sockfd = create_icmp_socket();
	if (sockfd < 0)
	{
		printf("Failed to create raw socket\n");
		return (1);
	}
	if (send_icmp_echo_request(sockfd, argv[1]) < 0)
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
	process_icmp_reply(reply_buffer, length);
	printf("Ping End\n");
	close(sockfd);
	return (0);
}