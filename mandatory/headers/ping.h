/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: insub <insub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 16:30:28 by insub             #+#    #+#             */
/*   Updated: 2026/01/26 13:52:58 by insub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PING_H
#define PING_H


#define PING_HELP \
"\nUsage\n"\
"  ping [options] <destination>\n"\
"\nOptions:\n"\
"  <destination>      dns name or ip address\n"\
"  -v                 verbose output\n"\
"  -?                 print help and exit\n"

#include <stdint.h>

typedef struct s_ping_options
{
	int		verbose;
}	t_ping_options;

extern t_ping_options	g_options; 

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