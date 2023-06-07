/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
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

void	ft_get_forks(t_env *env, t_philo *c_philo)
{
	pthread_mutex_lock(&(env->forks[c_philo->fork_1]));
	pthread_mutex_lock(&(env->message));
	ft_philo_write(env, c_philo, "has taken a fork");
	pthread_mutex_unlock(&(env->message));
	pthread_mutex_lock(&(env->forks[c_philo->fork_2]));
	pthread_mutex_lock(&(env->message));
	ft_philo_write(env, c_philo, "has taken a fork");
	pthread_mutex_unlock(&(env->message));
	pthread_mutex_lock(&(env->change));
	c_philo->last_meal = ft_gettime();
	pthread_mutex_unlock(&(env->change));
	pthread_mutex_lock(&(env->message));
	ft_philo_write(env, c_philo, "is eating");
	pthread_mutex_unlock(&(env->message));
}

void 	ft_eat(t_env *env, t_philo *c_philo)
{
	if (env->t_die <= env->t_eat)
	{
		usleep(env->t_die);
		pthread_mutex_lock(&(env->message));
		ft_philo_write(env, c_philo, "died");
		pthread_mutex_lock(&(env->change));
		env->death = 1;
		pthread_mutex_unlock(&(env->change));
		pthread_mutex_unlock(&(env->message));
		pthread_mutex_unlock(&(env->forks[c_philo->fork_1]));
		pthread_mutex_unlock(&(env->forks[c_philo->fork_2]));
		return ;
	}
	else
	{
		usleep(env->t_eat);
		pthread_mutex_lock(&(env->change));
		c_philo->m_eaten++;
		pthread_mutex_unlock(&(env->change));
		pthread_mutex_unlock(&(env->forks[c_philo->fork_1]));
		pthread_mutex_unlock(&(env->forks[c_philo->fork_2]));
	}
}

void 	ft_sleep(t_env *env, t_philo *c_philo)
{
	if ((ft_gettime() - c_philo->last_meal + env->t_sleep) < env->t_die)
	{
		pthread_mutex_lock(&(env->message));
		ft_philo_write(env, c_philo, "is sleeping");
		pthread_mutex_unlock(&(env->message));
		usleep(env->t_sleep);
	}
	else
	{
		pthread_mutex_lock(&(env->message));
		ft_philo_write(env, c_philo, "is sleeping");
		pthread_mutex_unlock(&(env->message));
		usleep(env->t_die - (ft_gettime() - c_philo->last_meal) + 1);
		pthread_mutex_lock(&(env->message));
		ft_philo_write(env, c_philo, "died");
		pthread_mutex_lock(&(env->change));
		env->death = 1;
		pthread_mutex_unlock(&(env->change));
		pthread_mutex_unlock(&(env->message));
	}
}

void 	ft_think(t_env *env, t_philo *c_philo)
{
	pthread_mutex_lock(&(env->message));
	ft_philo_write(env, c_philo, "is thinking");
	pthread_mutex_unlock(&(env->message));
}
