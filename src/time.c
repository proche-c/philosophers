/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proche-c <proche-c@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2022/01/25 12:11:31 by proche-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	ft_gettime(void)
{
	unsigned long	result;
	struct timeval	time;

	gettimeofday(&time, NULL);
	result = time.tv_sec * 1000000 + time.tv_usec;
	return (result);
}

unsigned long	ft_getlife(t_env *env, t_philo *c_philo)
{
	return (env->t_die - (ft_gettime() - env->last_meals[c_philo->num_p - 1]));
}

void	ft_usleep(t_env *env, unsigned long w_time)
{
	unsigned long	start;
	unsigned long	t_control;

	start = ft_gettime();
	while (1)
	{
		usleep(200);
		pthread_mutex_lock(&(env->change));
		t_control = ft_gettime() - start;
		pthread_mutex_unlock(&(env->change));
		if (t_control > w_time)
			return ;
		//pthread_mutex_unlock(&(env->change));
	}
}
