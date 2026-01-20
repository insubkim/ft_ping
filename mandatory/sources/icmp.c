/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   icmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: insub <insub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 19:01:20 by insub             #+#    #+#             */
/*   Updated: 2026/01/20 19:00:09 by insub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/ip_icmp.h>

#include "icmp.h"

int		send_icmp_echo_request(int sockfd, const char *ip_addr)
{
    struct hostent *host;
    struct sockaddr_in dest_addr;
    struct icmphdr icmp_hdr;

    host = gethostbyname(ip_addr);
    
    if (host == NULL)
    {
        perror("send_icmp_echo_request -gethostbyname");
        return (-1);
    }

    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = 0;
    dest_addr.sin_addr = *(struct in_addr *)host->h_addr;
    
    icmp_hdr.type = ICMP_ECHO;
    icmp_hdr.code = 0;
    icmp_hdr.checksum = 0;
    icmp_hdr.un.echo.id = getpid() & 0xFFFF;
    icmp_hdr.un.echo.sequence = 0;
    icmp_hdr.checksum = calculate_checksum((unsigned short *)&icmp_hdr, sizeof(icmp_hdr));

    if (sendto(sockfd, &icmp_hdr, sizeof(icmp_hdr), 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) < 0)
    {
        perror("send_icmp_echo_request - sendto");
        return (-1);
    }

    return (0);
}

int		receive_icmp_echo_reply(int sockfd, char *buffer, int buf_size)
{
    ssize_t length;
    length = recvfrom(sockfd, buffer, buf_size, 0, NULL, NULL);
    if (length < 0)
    {
        perror("receive_icmp_echo_reply - recvfrom");
        return (-1);
    }
    
    return ((int)length);
}

void	process_icmp_reply(const char *buffer, int length)
{
    struct iphdr *ip_hdr;
    int ip_hdr_len;
    struct icmphdr *icmp_hdr;

    if ((unsigned int)length < sizeof(struct iphdr) + sizeof(struct icmphdr))
    {
        printf("Received packet is too short\n");
        return;
    }
    
    ip_hdr = (struct iphdr *)buffer;
    ip_hdr_len = ip_hdr->ihl * 4;  // IP ���? ���� (���� 20����Ʈ)

    icmp_hdr = (struct icmphdr *)(buffer + ip_hdr_len);
    if (icmp_hdr->type == ICMP_ECHOREPLY)
    {
        printf("Received ICMP Echo Reply\n");
    }
    else
    {
        printf("Received non-echo reply ICMP packet\n");
    }

    printf("type : %d\n", icmp_hdr->type);
    printf("code : %d\n", icmp_hdr->code);
    printf("checksum : %0x\n", icmp_hdr->checksum);
    printf("id : %d\n", icmp_hdr->un.echo.id);
    printf("sequence : %d\n", icmp_hdr->un.echo.sequence);
    printf("\n");

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

unsigned short	calculate_checksum(unsigned short *buf, int len)
{
    unsigned long sum = 0;
    while (len > 1)
    {
        sum += *buf++;
        len -= 2;
    }
    if (len == 1)
    {
        sum += *(unsigned char *)buf;
    }
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    return (unsigned short)(~sum);
}