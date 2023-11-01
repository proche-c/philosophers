/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proche-c <proche-c@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2022/01/25 12:11:31 by proche-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **args)
{
	t_env	env;
	int		result;

	if (ft_check_parameters(ac, args) != 0)
		return (1);
	if (ft_init(ac, args, &env) != 0)
		return (1);
	result = ft_start_threads(&env);
	ft_unlock(&env);
	ft_destroy(&env);
	ft_free_env(&env);
	return (result);
}
