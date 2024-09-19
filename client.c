/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboiraza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:37:27 by iboiraza          #+#    #+#             */
/*   Updated: 2024/09/19 09:19:18 by iboiraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/ft_printf.h"
#include <signal.h>
#include <time.h>

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	num;

	i = 0;
	sign = 1;
	num = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	return (sign * num);
}

int	send_message(unsigned int pid, unsigned char *str)
{
	int	bits;
	int	i;

	i = 0;
	while (str[i])
	{
		bits = 8;
		while (--bits >= 0)
		{
			if ((str[i] >> bits) & 1)
			{
				if (kill(pid, SIGUSR2) == -1)
					return (1);
			}
			else
			{
				if (kill(pid, SIGUSR1) == -1)
					return (1);
			}
			usleep(700);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int	j;

	j = 0;
	if (argc != 3 || !argv[2])
		return (ft_printf("Usage : ./client <PID> <string to send>\n"), 1);
	while (argv[1][j] != '\0')
	{
		if (argv[1][j] < '0' || argv[1][j] > '9')
		{
			ft_printf("Wrong PID\n");
			return (1);
		}
		j++;
	}
	if (send_message(ft_atoi(argv[1]), (unsigned char *)argv[2]))
	{
		ft_printf("Client failed sending signal\n");
		return (1);
	}
	return (0);
}
