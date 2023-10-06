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

unsigned long	ft_getlife(t_env *env, t_philo *c_philo)
{
	return (env->t_die - (ft_gettime() - c_philo->last_meal));
}

void	ft_philo_write(t_env *env, t_philo *c_philo, char *str)
{
	unsigned long	time;

	if (env->death == 0)
	{
		time = ft_gettime() / 1000;
		printf("%lu %d %s\n", time, c_philo->num_p, str);
	}
}

int	ft_get_left(t_env *env, t_philo *c_philo)
{
	int	left;

	if (c_philo->num_p != 1 && c_philo->num_p != env->n_philos)
		left = c_philo->num_p - 1;
	else if (c_philo->num_p == 1)
		left = env->n_philos;
	else
		left = c_philo->num_p - 1;
	return (left);
}

int	ft_get_rigth(t_env *env, t_philo *c_philo)
{
	int	rigth;

	if (c_philo->num_p != 1 && c_philo->num_p != env->n_philos)
		rigth = c_philo->num_p + 1;
	else if (c_philo->num_p == 1)
		rigth = 2;
	else
		rigth = 1;
	return (rigth);
}

int	ft_check_death(t_env *env, t_philo *c_philo)
{
	int	left;
	int	rigth;
	unsigned long	life;
	unsigned long	t_rigth;
	unsigned long	t_left;

	pthread_mutex_lock(&(env->message));
	left = ft_get_left(env, c_philo);
	//printf("left: %d\n", left);
	rigth = ft_get_rigth(env, c_philo);
	//printf("rigth: %d\n", rigth);
	life = ft_getlife(env, c_philo);
	//printf("life: %lu\n", life);
	if (env->philo[left].eating == 1 || env->philo[rigth].eating == 1)
	{
		if (env->philo[left].eating == 1)
		{
			t_left = env->t_eat - (ft_gettime() - env->philo[left].last_meal);
			//printf("t_left: %lu\n", t_left);
		}
		else
			t_left = 0;
		if (env->philo[rigth].eating == 1)
		{
			t_rigth = env->t_eat - (ft_gettime() - env->philo[rigth].last_meal);
			//printf("t_rigth: %lu\n", t_rigth);
		}
		else
			t_left = 0;
		if (life < t_left || life < t_rigth)
		{
			env->death = 1;
			//ft_philo_write(env, c_philo, "IS GOING TO DIE");
			pthread_mutex_unlock(&(env->message));
			return ((int)life);
		}
	}
	//printf("env->death: %d\n", env->death);
	pthread_mutex_unlock(&(env->message));
	return (-1);
}

void	ft_eat(t_env *env, t_philo *c_philo)
{
	int	life;

	life = - 1;
	if (c_philo->num_p % 2 != 0 || (c_philo->num_p % 2 == 0 && (ft_gettime() - env->t_start) >= env->t_eat))
	{
		pthread_mutex_lock(&(env->forks[c_philo->fork_1]));
		pthread_mutex_lock(&(env->forks[c_philo->fork_2]));
		if (env->death == 0 && c_philo->finish == 0)
		{
			pthread_mutex_lock(&(env->change));
			c_philo->eating = 1;
			c_philo->last_meal = ft_gettime();
			pthread_mutex_lock(&(env->message));
			ft_philo_write(env, c_philo, "has taken a fork");
			ft_philo_write(env, c_philo, "has taken a fork");
			ft_philo_write(env, c_philo, "is eating");
			pthread_mutex_unlock(&(env->message));
			pthread_mutex_unlock(&(env->change));
		}
		usleep(env->t_eat);
		if (env->death == 0)
		{
			pthread_mutex_lock(&(env->change));
			c_philo->m_eaten++;
			c_philo->eating = 0;
			pthread_mutex_unlock(&(env->change));
			pthread_mutex_unlock(&(env->forks[c_philo->fork_1]));
			pthread_mutex_unlock(&(env->forks[c_philo->fork_2]));
			if (c_philo->m_eaten == env->n_meals)
			{
				pthread_mutex_lock(&(env->change));
				c_philo->finish = 1;
				pthread_mutex_unlock(&(env->change));
				return ;
			}
			pthread_mutex_lock(&(env->message));
			ft_philo_write(env, c_philo, "is sleeping");
			pthread_mutex_unlock(&(env->message));
			if (ft_getlife(env, c_philo) > env->t_sleep)
			{
				usleep(env->t_sleep);
				if (env->death == 0)
				{
					pthread_mutex_lock(&(env->message));
					ft_philo_write(env, c_philo, "is thinking");
					pthread_mutex_unlock(&(env->message));
					life = ft_check_death(env, c_philo);
					if (env->death == 1)
					{
						usleep(life);
						pthread_mutex_lock(&(env->message));
						ft_philo_write(env, c_philo, "died");
						usleep(7);
						pthread_mutex_unlock(&(env->message));
						return ;
					}

				}
			}
			else
			{
				usleep(ft_getlife(env, c_philo));
				if (env->death == 0)
				{
					pthread_mutex_lock(&(env->message));
					ft_philo_write(env, c_philo, "died");
					usleep(7);
					pthread_mutex_unlock(&(env->message));
					pthread_mutex_lock(&(env->change));
					env->death = 1;
					pthread_mutex_unlock(&(env->change));
					return ;
				}
			}
		}
	}
}
		

