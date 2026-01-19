/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: insub <insub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 18:06:04 by insub             #+#    #+#             */
/*   Updated: 2026/01/19 18:16:43 by insub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

#include "raw_socket.h"

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	printf("Ping Start\n");

	int sockfd = create_icmp_socket();
	if (sockfd < 0)
	{
		printf("Failed to create raw socket\n");
		return (1);
	}

	printf("Ping End\n");

	close(sockfd);
	return (0);
}