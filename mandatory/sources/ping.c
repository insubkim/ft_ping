/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: insub <insub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 16:52:04 by insub             #+#    #+#             */
/*   Updated: 2026/01/23 17:03:57 by insub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <stdio.h>
#include <stdint.h> 

#include "ping.h"

void print_ping_summary(t_ping_stats ping_stats, char *hostname)
{
    int64_t milliseconds = get_current_time_ms();

    printf("\n--- %s ping statistics ---\n", hostname);
    printf("%u packets transmitted, %u packets received, %.1f%% packet loss, time %ums\n",
           ping_stats.packets_sent,
           ping_stats.packets_received,
           (ping_stats.packets_sent == 0) ? 0.0 :
           ((ping_stats.packets_sent - ping_stats.packets_received) * 100.0) / ping_stats.packets_sent,
           milliseconds - ping_stats.ping_start_time_ms);
    
    if (ping_stats.packets_received == 0)
        return;

    printf("rtt min/avg/max/mdev = %.3f/%.3f/%.3f/%.3f ms\n",
           ping_stats.rtt_min,
           ping_stats.rtt_avg,
           ping_stats.rtt_max,
           ping_stats.rtt_mdev);
}

void set_ping_start_time_ms(t_ping_stats *ping_stats)
{
    ping_stats->ping_start_time_ms = (unsigned int)get_current_time_ms();
}


static int64_t	get_current_time_ms(void)
{
	struct timespec	spec;

	clock_gettime(CLOCK_REALTIME, &spec);
	return ((int64_t)spec.tv_sec * 1000 + (int64_t)spec.tv_nsec / 1000000);
}