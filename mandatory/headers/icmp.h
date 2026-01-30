/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   icmp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 19:01:28 by insub             #+#    #+#             */
/*   Updated: 2026/01/26 03:29:30 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICMP_H
# define ICMP_H

#include "ping.h"

int		send_icmp_echo_request(int sockfd, const char *ip_addr);
int		receive_icmp_echo_reply(int sockfd, char *buffer, int buf_size);
int		process_icmp_reply(const char *buffer, int length, t_ping_stats *ping_stats, int64_t ping_start_time_micro);

unsigned short	calculate_checksum(unsigned short *buf, int len);

char *icmp_type_to_string(int type);

#endif