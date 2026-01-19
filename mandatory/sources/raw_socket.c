/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw_socket.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: insub <insub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 18:08:54 by insub             #+#    #+#             */
/*   Updated: 2026/01/19 18:18:15 by insub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <netinet/in.h>

#include "raw_socket.h"

int create_raw_socket(void)
{
    int sockfd;

    sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
    if (sockfd < 0)
    {
        perror("socket");
        return -1;
    }
    return sockfd;
}

int create_icmp_socket(void)
{
    int sockfd;

    sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sockfd < 0)
    {
        perror("socket");
        return -1;
    }
    return sockfd;
}
