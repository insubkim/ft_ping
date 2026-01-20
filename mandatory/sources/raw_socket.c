/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw_socket.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: insub <insub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 18:08:54 by insub             #+#    #+#             */
/*   Updated: 2026/01/20 19:04:42 by insub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "raw_socket.h"

int	create_icmp_socket(void)
{
	int	sockfd;

	sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (sockfd < 0)
	{
		perror("socket");
		return (-1);
	}
	return (sockfd);
}


int set_socket_timeout(int sockfd, int timeout_sec)
{
    struct timeval timeout;
    timeout.tv_sec = timeout_sec;
    timeout.tv_usec = 0;

    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char *)&timeout, sizeof(timeout)) < 0)
    {
        perror("set_socket_timeout - setsockopt");
        return (-1);
    }
    return (0);
}
