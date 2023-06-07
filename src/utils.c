/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proche-c <proche-c@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2022/01/25 12:11:31 by proche-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r' || c == 32)
		return (1);
	return (0);
}

static int	ft_check_sign(char c)
{
	if (c == '-')
		return (-1);
	return (1);
}

unsigned long	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	unsigned long	num;
	unsigned long	result;

	i = 0;
	result = 0;
	sign = 1;
	while (ft_isspace(str[i]) == 1)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		sign = ft_check_sign(str[i]);
		i++;
	}
	while (str[i] > 47 && str[i] < 58)
	{
		num = str[i] - 48;
		result = result * 10 + num;
		i++;
	}
	return (result * sign);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}