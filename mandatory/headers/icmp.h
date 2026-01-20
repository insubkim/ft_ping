/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   icmp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: insub <insub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 19:01:28 by insub             #+#    #+#             */
/*   Updated: 2026/01/20 19:04:51 by insub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICMP_H
# define ICMP_H

int		send_icmp_echo_request(int sockfd, const char *ip_addr);
int		receive_icmp_echo_reply(int sockfd, char *buffer, int buf_size);
void	process_icmp_reply(const char *buffer, int length);

unsigned short	calculate_checksum(unsigned short *buf, int len);

char *icmp_type_to_string(int type);

#endif