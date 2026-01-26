/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw_socket.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 18:08:54 by insub             #+#    #+#             */
/*   Updated: 2026/01/26 03:25:33 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

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

char	*hostname_to_ipv4_addr(const char *hostname)
{
	static char			ip_str[INET_ADDRSTRLEN];
	struct addrinfo		hints;
	struct addrinfo		*res;
	struct sockaddr_in	*addr;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_RAW;
	if (getaddrinfo(hostname, NULL, &hints, &res) != 0)
		return (NULL);
	addr = (struct sockaddr_in *)res->ai_addr;
	if (inet_ntop(AF_INET, &addr->sin_addr, ip_str, sizeof(ip_str)) == NULL)
	{
		freeaddrinfo(res);
		return (NULL);
	}
	freeaddrinfo(res);
	return (ip_str);
}
