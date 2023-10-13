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

void	ft_check_philo_finish(t_env *env, t_philo *c_philo)
{
	if (c_philo->m_eaten == env->n_meals)
	{
		//pthread_mutex_lock(&(env->change));
		c_philo->finish = 1;
		//pthread_mutex_unlock(&(env->change));
		return ;
	}
}

void	ft_eat_even(t_env *env, t_philo *c_philo)
{

	if ((c_philo->num_p % 2 != 0 && env->round == 1)
		|| (c_philo->num_p % 2 == 0 && env->round == 2))
	{
			pthread_mutex_lock(&(env->forks[c_philo->fork_1]));
			pthread_mutex_lock(&(env->forks[c_philo->fork_2]));
			if (env->death == 0 && c_philo->finish == 0)
			{
				pthread_mutex_lock(&(env->change));
				c_philo->last_meal = ft_gettime();
				env->last_meals[c_philo->num_p - 1] = ft_gettime();
				pthread_mutex_unlock(&(env->change));
				pthread_mutex_lock(&(env->message));
				ft_philo_write(env, c_philo, "has taken a fork");
				ft_philo_write(env, c_philo, "has taken a fork");
				ft_philo_write(env, c_philo, "is eating");
				pthread_mutex_unlock(&(env->message));
				//pthread_mutex_unlock(&(env->change));
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
	//printf("ENTRO EN FT_EAT_TO_SLEEP\n");
	usleep(env->t_eat);
	if (env->death == 0)
	{
		pthread_mutex_lock(&(env->change));
		c_philo->m_eaten++;
		ft_update_round_even(env, c_philo);
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
			pthread_mutex_lock(&(env->message));
			ft_philo_write(env, c_philo, "is sleeping");
			pthread_mutex_unlock(&(env->message));
			ft_sleep_to_think(env, c_philo);
		}
	}
	else
	{
		pthread_mutex_unlock(&(env->forks[c_philo->fork_1]));
		pthread_mutex_unlock(&(env->forks[c_philo->fork_2]));
	}
}

void	ft_sleep_to_think(t_env *env, t_philo *c_philo)
{
	unsigned long	life;

	//printf("ENTRO EN FT_SLEEP_TO_THINK\n");
	pthread_mutex_lock(&(env->change));
	life = ft_getlife(env, c_philo);
	pthread_mutex_unlock(&(env->change));
	if (life <= env->t_sleep)
	{
		usleep(life);
		if (env->death == 0)
		{
			pthread_mutex_lock(&(env->change));
			//env->death = 1;
			pthread_mutex_lock(&(env->message));
			ft_philo_write(env, c_philo, "died");
			pthread_mutex_unlock(&(env->message));
			env->death = 1;
			pthread_mutex_unlock(&(env->change));
			return ;
		}
	}
	else
	{
		usleep(env->t_sleep);
		if (env->death == 0)
		{
			pthread_mutex_lock(&(env->message));
			ft_philo_write(env, c_philo, "is thinking");
			pthread_mutex_unlock(&(env->message));
			ft_thinking(env, c_philo);
		}
	}
}

void	ft_thinking(t_env *env, t_philo *c_philo)
{
	int	left;
	int	rigth;
	int	die;
	int	life;

	//printf("ENTRO EN FT_THINKING\n");
	pthread_mutex_lock(&(env->change));
	left = ft_get_left(env, c_philo);
	rigth = ft_get_rigth(env, c_philo);
	life = ft_getlife(env, c_philo);
	die = ft_check_death(env, c_philo, left, rigth);
	pthread_mutex_unlock(&(env->change));
	if (die == 1 && env->death == 0)
	{
		usleep(life);
		if (env->death == 0)
		{
			pthread_mutex_lock(&(env->change));
			//env->death = 1;
			pthread_mutex_lock(&(env->message));
			ft_philo_write(env, c_philo, "died");
			pthread_mutex_unlock(&(env->message));
			env->death = 1;
			pthread_mutex_unlock(&(env->change));
		}
	}	
}
