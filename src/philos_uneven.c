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
	if (c_philo->num_p == 1 || c_philo->num_p == 2 || c_philo->num_p == env->n_philos)
	{
		if (env->round == 1 || env->round == 2)
			env->round++;
		else if (env->round == 3)
			env->round = 1;
	}
}

void	ft_eat_uneven(t_env *env, t_philo *c_philo)
{
	if ((c_philo->num_p % 2 != 0 && c_philo->num_p != env->n_philos && env->round == 1)
		|| (c_philo->num_p % 2 == 0 && env->round == 2)
			|| (c_philo->num_p == env->n_philos && env->round == 3))
	{
		pthread_mutex_lock(&(env->forks[c_philo->fork_1]));
		pthread_mutex_lock(&(env->forks[c_philo->fork_2]));
		// printf("\n**** ROUND %d ****\n", env->round);
		// printf("ENTRO EN FT_EAT_UNEVEN\n");
		if (env->death == 0 && c_philo->finish == 0)
		{
			pthread_mutex_lock(&(env->change));
			c_philo->last_meal = ft_gettime();
			env->last_meals[c_philo->num_p - 1] = ft_gettime();
			pthread_mutex_lock(&(env->message));
			ft_philo_write(env, c_philo, "has taken a fork");
			ft_philo_write(env, c_philo, "has taken a fork");
			ft_philo_write(env, c_philo, "is eating");
			pthread_mutex_unlock(&(env->message));
			pthread_mutex_unlock(&(env->change));
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
	//printf("ENTRO EN FT_EAT_TO_SLEEP_UNEVEN\n");
	usleep(env->t_eat);
	if (env->death == 0)
	{
		pthread_mutex_lock(&(env->change));
		c_philo->m_eaten++;
		ft_update_round_uneven(env, c_philo);
		pthread_mutex_unlock(&(env->change));
		pthread_mutex_unlock(&(env->forks[c_philo->fork_1]));
		pthread_mutex_unlock(&(env->forks[c_philo->fork_2]));
		ft_check_philo_finish(env, c_philo);
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
}

// void	ft_routine_uneven(t_env *env, t_philo *c_philo)
// {
// 	//int	die;
// 	if ((c_philo->num_p % 2 != 0 && c_philo->num_p != env->n_philos && env->round == 1)
// 		|| (c_philo->num_p % 2 == 0 && env->round == 2)
// 			|| (c_philo->num_p == env->n_philos && env->round == 3))
// 	{
// 		pthread_mutex_lock(&(env->forks[c_philo->fork_1]));
// 		pthread_mutex_lock(&(env->forks[c_philo->fork_2]));
// 		if (env->death == 0 && c_philo->finish == 0)
// 		{
// 			pthread_mutex_lock(&(env->change));
// 			c_philo->eating = 1;
// 			c_philo->last_meal = ft_gettime();
// 			pthread_mutex_lock(&(env->message));
// 			ft_philo_write(env, c_philo, "has taken a fork");
// 			ft_philo_write(env, c_philo, "has taken a fork");
// 			ft_philo_write(env, c_philo, "is eating");
// 			pthread_mutex_unlock(&(env->message));
// 			pthread_mutex_unlock(&(env->change));
// 		}
// 		usleep(env->t_eat);
// 		if (env->death == 0)
// 		{
// 			pthread_mutex_lock(&(env->change));
// 			c_philo->m_eaten++;
// 			c_philo->eating = 0;
// 			ft_update_round_uneven(env, c_philo);
// 			pthread_mutex_unlock(&(env->change));
// 			pthread_mutex_unlock(&(env->forks[c_philo->fork_1]));
// 			pthread_mutex_unlock(&(env->forks[c_philo->fork_2]));
// 			if (c_philo->m_eaten == env->n_meals)
// 			{
// 				pthread_mutex_lock(&(env->change));
// 				c_philo->finish = 1;
// 				pthread_mutex_unlock(&(env->change));
// 				return ;
// 			}
// 			pthread_mutex_lock(&(env->message));
// 			ft_philo_write(env, c_philo, "is sleeping");
// 			pthread_mutex_unlock(&(env->message));
// 			if (ft_getlife(env, c_philo) > env->t_sleep)
// 			{
// 				usleep(env->t_sleep);
// 				if (env->death == 0)
// 				{
// 					pthread_mutex_lock(&(env->message));
// 					ft_philo_write(env, c_philo, "is thinking");
// 					pthread_mutex_unlock(&(env->message));
// 					//die = ft_check_death(env, c_philo);
// 					if (env->death == 1)
// 					{
// 						usleep(ft_getlife(env, c_philo));
// 						pthread_mutex_lock(&(env->message));
// 						ft_philo_write(env, c_philo, "died");
// 						usleep(7);
// 						pthread_mutex_unlock(&(env->message));
// 						return ;
// 					}

// 				}
// 			}
// 			else
// 			{
// 				usleep(ft_getlife(env, c_philo));
// 				if (env->death == 0)
// 				{
// 					pthread_mutex_lock(&(env->message));
// 					ft_philo_write(env, c_philo, "died");
// 					usleep(7);
// 					pthread_mutex_unlock(&(env->message));
// 					pthread_mutex_lock(&(env->change));
// 					env->death = 1;
// 					pthread_mutex_unlock(&(env->change));
// 					return ;
// 				}
// 			}
// 		}
// 	}
// }
		

