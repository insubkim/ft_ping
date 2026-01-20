/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw_socket.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: insub <insub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 18:08:15 by insub             #+#    #+#             */
/*   Updated: 2026/01/20 19:04:59 by insub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAW_SOCKET_H
# define RAW_SOCKET_H

int		create_icmp_socket(void);

int		set_socket_timeout(int sockfd, int timeout_sec);

#endif