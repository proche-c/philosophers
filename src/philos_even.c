/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_even.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proche-c <proche-c@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2022/01/25 12:11:31 by proche-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_update_round_even(t_env *env, t_philo *c_philo)
{
	if (c_philo->num_p == 1 || c_philo->num_p == 2)
	{
		if (env->round == 1)
			env->round++;
		else if (env->round == 2)
			env->round = 1;
	}
}

void	ft_eat_even(t_env *env, t_philo *c_philo)
{
	if ((c_philo->num_p % 2 != 0 && env->round == 1)
		|| (c_philo->num_p % 2 == 0 && env->round == 2))
	{
		pthread_mutex_lock(&(env->forks[c_philo->fork_1]));
		pthread_mutex_lock(&(env->forks[c_philo->fork_2]));
		//printf("ENTRO EN FT_EAT_EVEN\n");
		if (env->death == 0 && c_philo->finish == 0)
		{
			pthread_mutex_lock(&(env->change));
			env->last_meals[c_philo->num_p - 1] = ft_gettime();
			pthread_mutex_unlock(&(env->change));
			ft_print_eating(env, c_philo);
			ft_eat_to_sleep(env, c_philo);
		}
		else if (env->death == 1)
		{
			pthread_mutex_unlock(&(env->forks[c_philo->fork_1]));
			pthread_mutex_unlock(&(env->forks[c_philo->fork_2]));
		}
	}
}

void	ft_eat_to_sleep(t_env *env, t_philo *c_philo)
{
	//printf("philo %d ENTRA EN FT_EAT_TO_SLEEP\n", c_philo->num_p);
	ft_usleep(env, env->t_eat);
	//printf("philo %d DUERME\n", c_philo->num_p);
	if (env->death == 0)
	{
		pthread_mutex_lock(&(env->change));
		c_philo->m_eaten++;
		ft_update_round_even(env, c_philo);
		pthread_mutex_unlock(&(env->change));
		//printf("philo %d AUMENTA m_eaten a %d\n", c_philo->num_p, c_philo->m_eaten);
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

void	ft_sleep_to_think(t_env *env, t_philo *c_philo)
{
	unsigned long	life;

	//printf("philo %d ENTRA EN FT_SLEEP_TO_THINK\n", c_philo->num_p);
	pthread_mutex_lock(&(env->change));
	life = ft_getlife(env, c_philo);
	pthread_mutex_unlock(&(env->change));
	if (life <= env->t_sleep)
	{
		ft_usleep(env, life);
		if (env->death == 0)
		{
			ft_print_death(env, c_philo);
			return ;
		}
	}
	else
	{
		ft_usleep(env, env->t_sleep);
		if (env->death == 0)
		{
			ft_print_thinking(env, c_philo);
			ft_thinking(env, c_philo);
		}
	}
}

void	ft_thinking(t_env *env, t_philo *c_philo)
{
	int	die;
	int	life;

	//printf("philo %d ENTRA EN FT_THINKING\n", c_philo->num_p);
	pthread_mutex_lock(&(env->change));
	life = ft_getlife(env, c_philo);
	die = ft_check_death(env, c_philo, c_philo->left, c_philo->rigth);
	pthread_mutex_unlock(&(env->change));
	if (die == 1 && env->death == 0)
	{
		usleep(life);
		//printf("VA A MORIR\n");
		if (env->death == 0)
		{
			ft_print_death(env, c_philo);
		}
	}
}
