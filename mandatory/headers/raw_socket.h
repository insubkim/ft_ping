/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw_socket.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: insub <insub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 18:08:15 by insub             #+#    #+#             */
/*   Updated: 2026/01/30 14:38:14 by insub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAW_SOCKET_H
# define RAW_SOCKET_H

int		create_icmp_socket(void);

int		set_socket_timeout(int sockfd, int timeout_sec);
int		set_socket_ttl(int sockfd, int ttl_value);

char	*hostname_to_ipv4_addr(const char *hostname);

#endif