/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proche-c <proche-c@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2022/01/25 12:11:31 by proche-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_routine_one(void *args)
{
	t_philo	*c_philo;
	t_env	*env;

	c_philo = (t_philo *)args;
	env = c_philo->env;
	pthread_mutex_lock(&(env->forks[c_philo->fork_1]));
	pthread_mutex_lock(&(env->message));
	ft_philo_write(env, c_philo, "has taken a fork");
	pthread_mutex_unlock(&(env->message));
	usleep(env->t_die);
	ft_print_death(env, c_philo);
	pthread_mutex_lock(&(env->change));
	env->death = 1;
	pthread_mutex_unlock(&(env->change));
	pthread_mutex_unlock(&(env->forks[c_philo->fork_1]));
	return (NULL);
}

void	ft_die_eating(t_env *env, t_philo *c_philo)
{
	if ((env->n_philos % 2 == 0 && c_philo->num_p % 2 != 0)
		|| (env->n_philos % 2 != 0 && c_philo->num_p % 2 != 0
			&& c_philo->num_p % 2 != env->n_philos))
	{
		pthread_mutex_lock(&(env->forks[c_philo->fork_1]));
		pthread_mutex_lock(&(env->forks[c_philo->fork_2]));
		if (env->death == 0)
			ft_print_eating(env, c_philo);
		usleep(env->t_die);
		if (env->death == 0)
		{
			ft_print_death(env, c_philo);
		}
		pthread_mutex_unlock(&(env->forks[c_philo->fork_1]));
		pthread_mutex_unlock(&(env->forks[c_philo->fork_2]));
	}
}
