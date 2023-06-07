/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proche-c <proche-c@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2022/01/25 12:11:31 by proche-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_is_num(char c)
{
	if (c > 47 && c < 58)
		return (1);
	else
		return (0);
}

static int	ft_check_if_number(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] != '+' && ft_is_num(arg[i]) != 1)
		return (1);
	i++;
	while (arg[i] != '\0')
	{
		if (ft_is_num(arg[i]) != 1)
			return (1);
		i++;
	}
	return (0);
}

int	ft_check_parameters(int ac, char **args)
{
	int	i;

	if (ac != 5 && ac != 6)
	{
		printf("Wrong number of parameters\n");
		return (1);
	}
	else
	{
		i = 1;
		while (i < ac)
		{
			if (ft_check_if_number(args[i]) != 0)
			{
				printf("Wrong parameters, the argument %d is not a number\n", i);
				return(1);
			}
			i++;
		}
		i = 1;
		while (i < ac)
		{
			if (ft_atoi(args[i]) <= 0)
			{
				printf("Wrong parameters, arguments must be greater than 0\n");
				return (1);
			}
			i++;
		}
	}
	return (0);
}
