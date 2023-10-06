/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proche-c <proche-c@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2022/01/25 12:11:31 by proche-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void 	*ft_routine(void *args)
{
	t_philo	*c_philo;
	t_env	*env;
	int		stop;

	c_philo = (t_philo *)args;
	env = c_philo->env;
	stop = 0;
	while (stop < 1)
	{
		//if (env->n_philos % 2 == 0)
			ft_eat(env, c_philo);
		if (env->death == 1 || c_philo->finish == 1)
		{
			stop++;
			pthread_mutex_lock(&(env->message));
			printf("philo %d stop\n", c_philo->num_p);
			printf("env->death %d stop\n", env->death);
			printf("c_philo->finish %d stop\n", c_philo->finish);
			pthread_mutex_unlock(&(env->message));
		}
	}
	return (NULL);
}

int 	ft_start_threads(t_env *env)
{
	int	i;

	env->t_start = ft_gettime();
	if (env->n_philos == 1)
	{
		if (pthread_create(&env->philo[0].id, NULL, ft_routine_one, &(env->philo[0])) != 0)
			return (1);
		if (pthread_join(env->philo[0].id, NULL) != 0)
			return (1);
	}
	else
	{
		i = 0;
		while (i < env->n_philos)
		{
			env->philo[i].last_meal = env->t_start;
			if (pthread_create(&env->philo[i].id, NULL, ft_routine, &(env->philo[i])) != 0)
				return (1);
			pthread_mutex_lock(&(env->change));
			i++;
			pthread_mutex_unlock(&(env->change));
		}
		i = 0;
		while (i < env->n_philos)
		{
			if (pthread_join(env->philo[i].id, NULL) != 0)
				return (1);
			pthread_mutex_lock(&(env->change));
			i++;
			pthread_mutex_unlock(&(env->change));
		}
	}
	return (0);
}

