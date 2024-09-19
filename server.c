/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboiraza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:38:47 by iboiraza          #+#    #+#             */
/*   Updated: 2024/09/19 11:56:55 by iboiraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/ft_printf.h"
#include <signal.h>

void	handle_sigusr(int sigsent)
{
	static size_t	c = 0;
	static size_t	i = 0;

	if (sigsent == SIGUSR1)
		c = c << 1;
	else if (sigsent == SIGUSR2)
		c = (c << 1) | 1;
	i++;
	if (i == 8)
	{
		ft_printf("%c", c);
		i = 0;
		c = 0;
	}
}

int	main(void)
{
	ft_printf("SUCCESS!, Server is ready :D! The PID: %d\n", getpid());
	ft_printf("Waiting fot the string...\n");
	signal(SIGUSR1, handle_sigusr);
	signal(SIGUSR2, handle_sigusr);
	while (1)
	{
		pause();
	}
	return (0);
}
