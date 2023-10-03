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

void 	*ft_routine_one(void *args)
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
	pthread_mutex_lock(&(env->message));
	ft_philo_write(env, c_philo, "died");
	pthread_mutex_lock(&(env->change));
	env->death = 1;
	pthread_mutex_unlock(&(env->change));
	pthread_mutex_unlock(&(env->message));
	pthread_mutex_unlock(&(env->forks[c_philo->fork_1]));
	//ft_philo_write(env, c_philo, "created");
	// while (1)
	// {
	// 	if (ft_check_death(env, c_philo) == 1)
	// 		break;
	// 	else
	// 	{
	// 		ft_get_forks(env, c_philo);
	// 		ft_eat(env, c_philo);
	// 	}
	//  	if (ft_check_death(env, c_philo) == 1)
	//  		break;
	//  	else
	//  		ft_sleep(env, c_philo);
	//  	if (ft_check_death(env, c_philo) == 1)
	//  		break;
	//  	else
	//  		ft_think(env, c_philo);
	// 	if (ft_check_death(env, c_philo) == 1)
	//  		break;
	// }
	return (NULL);
}


