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

	c_philo = (t_philo *)args;
	env = c_philo->env;
	while (1)
	{
		if (env->start == 1)
			break ;
	}
	while (env->death == 0 && c_philo->finish == 0)
	{
		if (env->t_die <= env->t_eat)
			ft_die_eating(env, c_philo);
		else if (env->n_philos % 2 == 0)
			ft_eat_even(env, c_philo);
		else
			ft_eat_uneven(env, c_philo);
	}
	return (NULL);
}

int 	ft_start_one_philo(t_env *env)
{
	if (pthread_create(&env->philo[0].id, NULL, ft_routine_one, &(env->philo[0])) != 0)
		return (1);
	if (pthread_join(env->philo[0].id, NULL) != 0)
		return (1);
	return (0);
}

int 	ft_start_multiphilos(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->n_philos)
	{
		if (pthread_create(&env->philo[i].id, NULL, ft_routine, &(env->philo[i])) != 0)
			return (1);
		pthread_mutex_lock(&(env->change));
		i++;
		pthread_mutex_unlock(&(env->change));
		if (i == env->n_philos)
		{
			pthread_mutex_lock(&(env->change));
			env->start = 1;
			pthread_mutex_unlock(&(env->change));
		}
	}
	return (0);
}

int 	ft_start_threads(t_env *env)
{
	int	i;
	//int	result;

	env->t_start = ft_gettime();
	if (env->n_philos == 1)
		return (ft_start_one_philo(env));
	else
	{
		i = 0;
		while (i < env->n_philos)
		{
			env->last_meals[i] = env->t_start;
			i++;
		}
		if (ft_start_multiphilos(env) == 1)
			return (1);
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

