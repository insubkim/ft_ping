/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: insub <insub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 16:30:28 by insub             #+#    #+#             */
/*   Updated: 2026/01/23 17:01:57 by insub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PING_H
#define PING_H

#define PING_USAGE \
"usage: ping [-AaDdfnoQqRrv] [-c count] [-G sweepmaxsize]\n" \
"            [-g sweepminsize] [-h sweepincrsize] [-i wait]\n" \
"            [-l preload] [-M mask | time] [-m ttl] [-p pattern]\n" \
"            [-S src_addr] [-s packetsize] [-t timeout][-W waittime]\n" \
"            [-z tos] host\n" \
"       ping [-AaDdfLnoQqRrv] [-c count] [-I iface] [-i wait]\n" \
"            [-l preload] [-M mask | time] [-m ttl] [-p pattern] [-S src_addr]\n"\
"            [-s packetsize] [-T ttl] [-t timeout] [-W waittime]\n"\
"            [-z tos] mcast-group\n"\
"Apple specific options (to be specified before mcast-group or host like all options)\n"\
"            -b boundif           # bind the socket to the interface\n"\
"            -k traffic_class     # set traffic class socket option\n"\
"            -K net_service_type  # set traffic class socket options\n"\
"            --apple-connect      # call connect(2) in the socket\n"\
"            --apple-time         # display current time\n"\
"            --apple-print-id     # display echo ID\n"\
"            --apple-print-req    # display echo request\n"

typedef struct s_ping_stats
{
    unsigned int    packets_sent;
    unsigned int    packets_received;
    unsigned int    packets_lost;
    unsigned int    ping_start_time_ms;
    double          rtt_min;
    double          rtt_max;
    double          rtt_avg;
    double          rtt_mdev;
}				t_ping_stats;

void print_ping_summary(t_ping_stats ping_stats, char *hostname);

void set_ping_start_time_ms(t_ping_stats *ping_stats);

static int64_t	get_current_time_ms(void);

#endif 