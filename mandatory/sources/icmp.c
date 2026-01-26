/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   icmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 19:01:20 by insub             #+#    #+#             */
/*   Updated: 2026/01/26 03:01:22 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netdb.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>

#include "icmp.h"
#include "ping.h"

#define ICMP_HDR_SIZE	8
#define ICMP_DATA_SIZE	56

typedef struct s_icmp_packet
{
	struct icmphdr	hdr;
	char			data[ICMP_DATA_SIZE];
}	t_icmp_packet;

static void	fill_icmp_data(char *data, int size)
{
	struct timeval	tv;
	int				i;

	gettimeofday(&tv, NULL);
	memcpy(data, &tv, sizeof(tv));
	i = sizeof(tv);
	while (i < size)
	{
		data[i] = 0x10 + (i - sizeof(tv));
		i++;
	}
}

int		send_icmp_echo_request(int sockfd, const char *ip_addr)
{
	struct sockaddr_in	dest_addr;
	t_icmp_packet		packet;

	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = 0;
	inet_pton(AF_INET, ip_addr, &dest_addr.sin_addr);

	memset(&packet, 0, sizeof(packet));
	packet.hdr.type = ICMP_ECHO;
	packet.hdr.code = 0;
	packet.hdr.un.echo.id = getpid() & 0xFFFF;
	packet.hdr.un.echo.sequence = 0;
	fill_icmp_data(packet.data, ICMP_DATA_SIZE);
	packet.hdr.checksum = calculate_checksum((unsigned short *)&packet,
			sizeof(packet));

	if (sendto(sockfd, &packet, sizeof(packet), 0,
			(struct sockaddr *)&dest_addr, sizeof(dest_addr)) < 0)
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

void	process_icmp_reply(const char *buffer, int length, t_ping_stats *ping_stats, unsigned int ping_start_time_micro)
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
    ip_hdr_len = ip_hdr->ihl * 4;  

    icmp_hdr = (struct icmphdr *)(buffer + ip_hdr_len);

    // set ping initial time
    if (ping_stats->ping_start_time_ms == 0)
    {
        ping_stats->ping_start_time_ms = ping_start_time_micro / 1000;
    }
    ping_stats->packets_sent++;
    if (icmp_hdr->type == ICMP_ECHOREPLY)
    {
        ping_stats->packets_received++;
        ping_stats->packets_lost = ping_stats->packets_sent - ping_stats->packets_received;
    }
    else
    {
        printf("Received non-echo reply ICMP packet\n");
    }

    int64_t microseconds = get_current_time_micro();
    printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%.3f ms\n", length - ip_hdr_len,
           inet_ntoa(*(struct in_addr *)&ip_hdr->saddr),
           ntohs(icmp_hdr->un.echo.sequence),
           ip_hdr->ttl,
           microseconds - ping_start_time_micro / 1000.0);
}

char *icmp_type_to_string(int type)
{
    switch (type)
    {
        case ICMP_ECHOREPLY:
            return "Echo Reply";
        case ICMP_DEST_UNREACH:
            return "Destination Unreachable";
        case ICMP_SOURCE_QUENCH:
            return "Source Quench";
        case ICMP_REDIRECT:
            return "Redirect";
        case ICMP_ECHO:
            return "Echo Request";
        case ICMP_TIME_EXCEEDED:
            return "Time Exceeded";
        case ICMP_PARAMETERPROB:
            return "Parameter Problem";
        case ICMP_TIMESTAMP:
            return "Timestamp Request";
        case ICMP_TIMESTAMPREPLY:
            return "Timestamp Reply";
        case ICMP_INFO_REQUEST:
            return "Information Request";
        case ICMP_INFO_REPLY:
            return "Information Reply";
        default:
            return "Unknown Type";
    }
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