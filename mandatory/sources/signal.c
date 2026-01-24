/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: insub <insub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 17:09:18 by insub             #+#    #+#             */
/*   Updated: 2026/01/24 17:21:32 by insub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>

#include "ping.h"

void	sig_handler(int sig)
{
	if (sig == SIGINT || 
        sig == SIGQUIT)
	{
        g_summary_flag = 1;
	}
    else
    {
        printf("Received unknown signal on sig handler: %d\n", sig);
    }
    return ;
}

void	set_signal(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
}
