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
	else if (c_philo->num_p == env->n_philos)
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
	else if (c_philo->num_p == env->n_philos)
		rigth = 1;
	return (rigth);
}

int	ft_check_death(t_env *env, t_philo *c_philo)
{
	int	left;
	int	rigth;

	left = ft_get_left(env, c_philo);
	rigth = ft_get_rigth(env, c_philo);
	if (c_philo->num_p != 1 && c_philo->num_p != env->n_philos)
	{
		left = c_philo->num_p - 1;
		rigth = c_philo->num_p + 1;
	}
	else if (c_philo->num_p == 1)
	{
		left = env->n_philos;
		rigth = 2;
	}
	else if (c_philo->num_p == env->n_philos)
	{
		left = c_philo->num_p - 1;
		rigth = 1;
	}
}

void	ft_get_forks(t_env *env, t_philo *c_philo)
{
	if (env->death == 0 && c_philo->finish == 0)
	{
		if (c_philo->num_p % 2 != 0)
		{
			if (ft_check_death(env, c_philo) == 1)
				return ;
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
					c_philo->finish = 1;
					//pthread_mutex_unlock(&(env->change));
					return ;
				}
				pthread_mutex_lock(&(env->message));
				ft_philo_write(env, c_philo, "is sleeping");
				pthread_mutex_unlock(&(env->message));
				//pthread_mutex_unlock(&(env->change));
				if (ft_getlife(env, c_philo) > env->t_sleep)
				{
					usleep(env->t_sleep);
					if (env->death == 0)
					{
						pthread_mutex_lock(&(env->message));
						ft_philo_write(env, c_philo, "is thinking");
						pthread_mutex_unlock(&(env->message));
					}
				}
				else
				{
					usleep(ft_getlife(env, c_philo));
					//pthread_mutex_lock(&(env->change));
					if (env->death == 0)
					{
						pthread_mutex_lock(&(env->message));
						ft_philo_write(env, c_philo, "died");
						pthread_mutex_unlock(&(env->message));
						env->death = 1;
					}
					//pthread_mutex_unlock(&(env->change));
				}
			}
		}
		else if (c_philo->num_p % 2 == 0 && (ft_gettime() - env->t_start) >= env->t_eat)
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
					c_philo->finish = 1;
					//pthread_mutex_unlock(&(env->change));
					return ;
				}
				pthread_mutex_lock(&(env->message));
				ft_philo_write(env, c_philo, "is sleeping");
				pthread_mutex_unlock(&(env->message));
				//pthread_mutex_unlock(&(env->change));
				if (ft_getlife(env, c_philo) > env->t_sleep)
				{
					usleep(env->t_sleep);
					if (env->death == 0)
					{
						pthread_mutex_lock(&(env->message));
						ft_philo_write(env, c_philo, "is thinking");
						pthread_mutex_unlock(&(env->message));
					}
				}
				else
				{
					usleep(ft_getlife(env, c_philo));
					//pthread_mutex_lock(&(env->change));
					if (env->death == 0)
					{
						pthread_mutex_lock(&(env->message));
						ft_philo_write(env, c_philo, "died");
						pthread_mutex_unlock(&(env->message));
						env->death = 1;
					}
					//pthread_mutex_unlock(&(env->change));
				}
			}
		}
	}
}

// void	ft_get_forks_uneven(t_env *env, t_philo *c_philo)
// {
// 	if ((ft_gettime() - c_philo->last_meal) >= env->t_die)
// 	{
// 		pthread_mutex_lock(&(env->message));
// 		ft_philo_write(env, c_philo, "died");
// 		pthread_mutex_unlock(&(env->message));
// 		pthread_mutex_lock(&(env->change));
// 		env->death = 1;
// 		pthread_mutex_unlock(&(env->change));
// 	}
// 	if (env->death == 0 && c_philo->finish == 0)
// 	{
// 		if (c_philo->num_p % 2 != 0 && c_philo->num_p != env->n_philos)
// 		{
// 			pthread_mutex_lock(&(env->forks[c_philo->fork_1]));
// 			pthread_mutex_lock(&(env->forks[c_philo->fork_2]));
// 			c_philo->last_meal = ft_gettime();
// 			pthread_mutex_lock(&(env->message));
// 			ft_philo_write(env, c_philo, "has taken a fork");
// 			ft_philo_write(env, c_philo, "has taken a fork");
// 			ft_philo_write(env, c_philo, "is eating");
// 			pthread_mutex_unlock(&(env->message));
// 		}
// 		else if (c_philo->num_p % 2 == 0 && (ft_gettime() - env->t_start) >= env->t_eat)
// 		{
// 			pthread_mutex_lock(&(env->forks[c_philo->fork_1]));
// 			pthread_mutex_lock(&(env->forks[c_philo->fork_2]));
// 			pthread_mutex_lock(&(env->change));
// 			c_philo->last_meal = ft_gettime();
// 			pthread_mutex_unlock(&(env->change));
// 			pthread_mutex_lock(&(env->message));
// 			ft_philo_write(env, c_philo, "has taken a fork");
// 			ft_philo_write(env, c_philo, "has taken a fork");
// 			ft_philo_write(env, c_philo, "is eating");
// 			pthread_mutex_unlock(&(env->message));
// 		}
// 		else if (c_philo->num_p == env->n_philos && ((ft_gettime() - env->t_start) >= (env->t_eat + 1)))
// 		{
// 			pthread_mutex_lock(&(env->forks[c_philo->fork_1]));
// 			pthread_mutex_lock(&(env->forks[c_philo->fork_2]));
// 			pthread_mutex_lock(&(env->change));
// 			c_philo->last_meal = ft_gettime();
// 			pthread_mutex_unlock(&(env->change));
// 			pthread_mutex_lock(&(env->message));
// 			ft_philo_write(env, c_philo, "has taken a fork");
// 			ft_philo_write(env, c_philo, "has taken a fork");
// 			ft_philo_write(env, c_philo, "is eating");
// 			pthread_mutex_unlock(&(env->message));
// 		}
// 	}
// }

// void 	ft_eat(t_env *env, t_philo *c_philo)
// {
// 	if (ft_gettime() + env->t_eat >= c_philo->last_meal + env->t_die)
// 	{
// 		usleep((c_philo->last_meal + env->t_die) - ft_gettime());
// 		pthread_mutex_lock(&(env->change));
// 		if (env->death == 0 && c_philo->finish == 0)
// 		{
// 			pthread_mutex_lock(&(env->message));
// 			ft_philo_write(env, c_philo, "died");
// 			pthread_mutex_unlock(&(env->message));
// 			//pthread_mutex_lock(&(env->change));
// 			env->death = 1;
// 		}
// 		pthread_mutex_unlock(&(env->change));
// 		pthread_mutex_unlock(&(env->forks[c_philo->fork_1]));
// 		pthread_mutex_unlock(&(env->forks[c_philo->fork_2]));
// 		//pthread_mutex_unlock(&(env->change));
// 	}
// 	else
// 	{
// 		usleep(env->t_eat);
// 		pthread_mutex_lock(&(env->change));
// 		if (env->death == 0 && c_philo->finish == 0)
// 		{
// 			c_philo->m_eaten++;
// 			if (env->n_meals > 0)
// 			{
// 				if (c_philo->m_eaten == env->n_meals)
// 				{
// 					c_philo->finish = 1;
// 				}
// 			}
// 			if (c_philo->finish == 0)
// 			{
// 				pthread_mutex_lock(&(env->message));
// 				ft_philo_write(env, c_philo, "is sleeping");
// 				pthread_mutex_unlock(&(env->message));
// 			}
// 		}
// 		pthread_mutex_unlock(&(env->forks[c_philo->fork_1]));
// 		pthread_mutex_unlock(&(env->forks[c_philo->fork_2]));
// 		pthread_mutex_unlock(&(env->change));
// 	}
// }

// void 	ft_sleep(t_env *env, t_philo *c_philo)
// {
// 	if ((ft_gettime() + env->t_sleep) >= c_philo->last_meal + env->t_die)
// 	{
// 		usleep((c_philo->last_meal + env->t_die) - ft_gettime());
// 		pthread_mutex_lock(&(env->change));
// 		if (env->death == 0 || c_philo->finish == 0)
// 		{
// 			pthread_mutex_lock(&(env->message));
// 			ft_philo_write(env, c_philo, "died");
// 			pthread_mutex_unlock(&(env->message));
// 			env->death = 1;
// 		}
// 		pthread_mutex_unlock(&(env->change));
// 	}
// 	else
// 	{
// 		usleep(env->t_sleep);
// 		pthread_mutex_lock(&(env->change));
// 		if (env->death == 0 && c_philo->finish == 0)
// 		{
// 			pthread_mutex_lock(&(env->message));
// 			ft_philo_write(env, c_philo, "is thinking");
// 			pthread_mutex_unlock(&(env->message));
// 		}
// 		pthread_mutex_unlock(&(env->change));
// 	}
// }

