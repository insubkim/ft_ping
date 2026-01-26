/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 16:30:28 by insub             #+#    #+#             */
/*   Updated: 2026/01/26 04:13:36 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PING_H
#define PING_H

#define PING_USAGE \
"Usage: ping [-aAbBdDfhLnOqrRUvV64] [-c count] [-i interval] [-I interface]\n"\
"            [-m mark] [-M pmtudisc_option] [-l preload] [-p pattern] [-Q tos]\n"\
"            [-s packetsize] [-S sndbuf] [-t ttl] [-T timestamp_option]\n"\
"            [-w deadline] [-W timeout] [hop1 ...] destination\n"\
"Usage: ping -6 [-aAbBdDfhLnOqrRUvV] [-c count] [-i interval] [-I interface]\n"\
"             [-l preload] [-m mark] [-M pmtudisc_option]\n"\
"             [-N nodeinfo_option] [-p pattern] [-Q tclass] [-s packetsize]\n"\
"             [-S sndbuf] [-t ttl] [-T timestamp_option] [-w deadline]\n"\
"             [-W timeout] destination\n"\

#include <stdint.h> 

typedef struct s_ping_stats
{
    unsigned int    packets_sent;
    unsigned int    packets_received;
    unsigned int    packets_lost;
    int64_t         ping_start_time_ms;
    double          rtt_min;
    double          rtt_max;
    double          rtt_avg;
    double          rtt_mdev;
    double          rtt_ss; // 제곱 편차 합. rtt_mdev 계산용.  
}				t_ping_stats;

extern int	g_summary_flag;

void print_ping_summary(t_ping_stats ping_stats, char *hostname);

int64_t	get_current_time_micro(void);

#endif 