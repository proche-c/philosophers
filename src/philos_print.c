/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proche-c <proche-c@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2022/01/25 12:11:31 by proche-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_philo_write(t_env *env, t_philo *c_philo, char *str)
{
	unsigned long	time;

	if (env->death == 0)
	{
		time = ft_gettime() / 1000;
		printf("%lu %d %s\n", time, c_philo->num_p, str);
	}
}

void	ft_print_eating(t_env *env, t_philo *c_philo)
{
	pthread_mutex_lock(&(env->message));
	ft_philo_write(env, c_philo, "has taken a fork");
	ft_philo_write(env, c_philo, "has taken a fork");
	ft_philo_write(env, c_philo, "is eating");
	pthread_mutex_unlock(&(env->message));
}

void	ft_print_sleeping(t_env *env, t_philo *c_philo)
{
	pthread_mutex_lock(&(env->message));
	ft_philo_write(env, c_philo, "is sleeping");
	pthread_mutex_unlock(&(env->message));
}

void	ft_print_thinking(t_env *env, t_philo *c_philo)
{
	pthread_mutex_lock(&(env->message));
	ft_philo_write(env, c_philo, "is thinking");
	pthread_mutex_unlock(&(env->message));
}

void	ft_print_die_and_print(t_env *env, t_philo *c_philo)
{
		pthread_mutex_lock(&(env->message));
		ft_philo_write(env, c_philo, "died");
		pthread_mutex_unlock(&(env->message));
}
