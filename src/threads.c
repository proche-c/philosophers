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

int	ft_check_death(t_env *env, t_philo *c_philo)
{
	printf("Check death\n");
	if (env->death == 1)
		return (1);
	if ((ft_gettime() - c_philo->last_meal) >= env->t_die)
	{
		pthread_mutex_lock(&(env->change));
		env->death = 1;
		pthread_mutex_unlock(&(env->change));
		return (1);
	}
	if (env->meals == 1 && c_philo->m_eaten == env->n_meals)
		return (1);
	return (0);
}

void 	*ft_routine(void *args)
{
	t_philo	*c_philo;
	t_env	*env;

	c_philo = (t_philo *)args;
	env = c_philo->env;
	ft_philo_write(env, c_philo, "created");
	while (1)
	{
		if (ft_check_death(env, c_philo) == 1)
			break;
		else
		{
			ft_get_forks(env, c_philo);
			ft_eat(env, c_philo);
		}
	 	if (ft_check_death(env, c_philo) == 1)
	 		break;
	 	else
	 		ft_sleep(env, c_philo);
	 	if (ft_check_death(env, c_philo) == 1)
	 		break;
	 	else
	 		ft_think(env, c_philo);
		if (ft_check_death(env, c_philo) == 1)
	 		break;
	}
	return (NULL);
}

int 	ft_start_threads(t_env *env)
{
	int	i;

	env->t_start = ft_gettime();
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
	return (0);
}

