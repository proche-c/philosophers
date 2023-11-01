/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proche-c <proche-c@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2022/01/25 12:11:31 by proche-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_check_philo_finish(t_env *env, t_philo *c_philo)
{
	if (c_philo->m_eaten == env->n_meals)
	{
		c_philo->finish = 1;
		return ;
	}
}

int	ft_get_left(t_env *env, int i)
{
	int	left;

	if (i == 0)
		left = env->n_philos - 1;
	else
		left = i - 1;
	return (left);
}

int	ft_get_rigth(t_env *env, int i)
{
	int	rigth;

	if (i == env->n_philos - 1)
		rigth = 0 ;
	else
		rigth = i + 1;
	return (rigth);
}

int	ft_check_death(t_env *env, t_philo *c_philo, int left, int rigth)
{
	unsigned long	life;
	unsigned long	time;
	unsigned long	t_rigth;
	unsigned long	t_left;

	//pthread_mutex_lock(&(env->change));
	time = ft_gettime();
	life = ft_getlife(env, c_philo);
	// printf("Time: %lu\n", time);
	// printf("philo %d lasta meal was %lu\n", c_philo->num_p, env->last_meals[c_philo->num_p - 1]);
	// printf("life left: %lu\n", life);
	if ((env->last_meals[left] + env->t_eat) >= time
		&& (env->last_meals[rigth] + env->t_eat) >= time)
	{
		t_left = env->last_meals[left] + env->t_eat - time;
		t_rigth = env->last_meals[rigth] + env->t_eat - time;
		//printf("t_left: %lu\n", t_left);
		//printf("t_rigth: %lu\n", t_rigth);
		//pthread_mutex_unlock(&(env->change));
		if (t_left < t_rigth)
		{
			if (life < t_left)
				return (1);
		}
		else
		{
			if (life < t_rigth)
				return (1);
		}
	}
	//pthread_mutex_unlock(&(env->change));
	return (0);
}
