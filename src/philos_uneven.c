/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_uneven.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proche-c <proche-c@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2022/01/25 12:11:31 by proche-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_update_round_uneven(t_env *env, t_philo *c_philo)
{
	if (c_philo->num_p == 1 || c_philo->num_p == 2
		|| c_philo->num_p == env->n_philos)
	{
		if (env->round == 1 || env->round == 2)
			env->round++;
		else if (env->round == 3)
			env->round = 1;
	}
}

void	ft_eat_uneven(t_env *env, t_philo *c_philo)
{
	if ((c_philo->num_p % 2 != 0 && c_philo->num_p != env->n_philos
			&& env->round == 1) || (c_philo->num_p % 2 == 0 && env->round == 2)
		|| (c_philo->num_p == env->n_philos && env->round == 3))
	{
		pthread_mutex_lock(&(env->forks[c_philo->fork_1]));
		pthread_mutex_lock(&(env->forks[c_philo->fork_2]));
		if (env->death == 0 && c_philo->finish == 0)
		{
			pthread_mutex_lock(&(env->change));
			env->last_meals[c_philo->num_p - 1] = ft_gettime();
			pthread_mutex_unlock(&(env->change));
			ft_print_eating(env, c_philo);
			ft_eat_to_sleep_uneven(env, c_philo);
		}
		else if (env->death == 1)
		{
			pthread_mutex_unlock(&(env->forks[c_philo->fork_1]));
			pthread_mutex_unlock(&(env->forks[c_philo->fork_2]));
		}
	}
}

void	ft_eat_to_sleep_uneven(t_env *env, t_philo *c_philo)
{
	usleep(env->t_eat);
	if (env->death == 0)
	{
		pthread_mutex_lock(&(env->change));
		c_philo->m_eaten++;
		ft_update_round_uneven(env, c_philo);
		pthread_mutex_unlock(&(env->change));
		pthread_mutex_unlock(&(env->forks[c_philo->fork_1]));
		pthread_mutex_unlock(&(env->forks[c_philo->fork_2]));
		pthread_mutex_lock(&(env->change));
		ft_check_philo_finish(env, c_philo);
		pthread_mutex_unlock(&(env->change));
		if (c_philo->finish == 1)
			return ;
		if (env->death == 0)
		{
			ft_print_sleeping(env, c_philo);
			ft_sleep_to_think(env, c_philo);
		}
	}
}
