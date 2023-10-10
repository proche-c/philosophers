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
		time = ft_gettime();
		printf("%lu %d %s\n", time, c_philo->num_p, str);
	}
}

int	ft_get_left(t_env *env, t_philo *c_philo)
{
	int	left;

	if (c_philo->num_p != 1 && c_philo->num_p != env->n_philos)
		left = c_philo->num_p - 2;
	else if (c_philo->num_p == 1)
		left = env->n_philos - 1;
	else
		left = c_philo->num_p - 2;
	return (left);
}

int	ft_get_rigth(t_env *env, t_philo *c_philo)
{
	int	rigth;

	if (c_philo->num_p != 1 && c_philo->num_p != env->n_philos)
		rigth = c_philo->num_p ;
	else if (c_philo->num_p == 1)
		rigth = 1;
	else
		rigth = 0;
	return (rigth);
}

void	ft_check_death(t_env *env, t_philo *c_philo)
{
	int	left;
	int	rigth;
	unsigned long	life;
	unsigned long	time;
	unsigned long	t_rigth;
	unsigned long	t_left;

	time = ft_gettime();
	printf("\n**** %d *****\n", c_philo->num_p);
	printf("time: %lu\n", ft_gettime());
	left = ft_get_left(env, c_philo);
	rigth = ft_get_rigth(env, c_philo);
	life = ft_getlife(env, c_philo);
	printf("philo left: %d\n", left);
	printf("philo rigth: %d\n", rigth);
	if ((env->last_meals[left] + env->t_eat) >= time && (env->last_meals[rigth] + env->t_eat) >= time)
	{
		printf("los de al lado estan comiendo\n");
		t_left = env->last_meals[left] + env->t_eat - time;
		t_rigth = env->last_meals[rigth] + env->t_eat - time;
		printf("al de la izquierda le quedan %lu\n", t_left);
		printf("al de la derecha le quedan %lu\n", t_rigth);
		printf("a %d le quedan %lu de vida\n", c_philo->num_p, life);
		if (t_left < t_rigth)
		{
			if (life < t_left)
			{
				env->death = 1;
				pthread_mutex_lock(&(env->message));
				ft_philo_write(env, c_philo, "WILL DIE");
				pthread_mutex_unlock(&(env->message));
			}
		}
		else
		{
			if (life < t_rigth)
			{
				env->death = 1;
				pthread_mutex_lock(&(env->message));
				ft_philo_write(env, c_philo, "WILL DIE");
				pthread_mutex_unlock(&(env->message));
			}
		}
	}
}

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
void	ft_eat_even(t_env *env, t_philo *c_philo)
{
	if ((c_philo->num_p % 2 != 0 && env->round == 1)
		|| (c_philo->num_p % 2 == 0 && env->round == 2))
	{
		pthread_mutex_lock(&(env->forks[c_philo->fork_1]));
		pthread_mutex_lock(&(env->forks[c_philo->fork_2]));
		printf("\n**** ROUND %d ****\n", env->round);
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
			ft_to_sleep(env, c_philo);
		}
	}
}
void	ft_check_philo_finish(t_env *env, t_philo *c_philo)
{
	if (c_philo->m_eaten == env->n_meals)
	{
		pthread_mutex_lock(&(env->change));
		c_philo->finish = 1;
		pthread_mutex_unlock(&(env->change));
		return ;
	}
}

void	ft_to_sleep(t_env *env, t_philo *c_philo)
{
	if (ft_getlife(env, c_philo) > env->t_eat)
	{
		usleep(env->t_eat);
		if (env->death == 0)
		{
			pthread_mutex_lock(&(env->change));
			c_philo->m_eaten++;
			ft_update_round_even(env, c_philo);
			pthread_mutex_unlock(&(env->change));
			pthread_mutex_unlock(&(env->forks[c_philo->fork_1]));
			pthread_mutex_unlock(&(env->forks[c_philo->fork_2]));
			ft_check_philo_finish(env, c_philo);
			if (c_philo->finish == 1)
				return ;
			pthread_mutex_lock(&(env->change));
			if (env->death == 0)
			{
				pthread_mutex_lock(&(env->change));
				pthread_mutex_lock(&(env->message));
				ft_philo_write(env, c_philo, "is sleeping");
				pthread_mutex_unlock(&(env->message));
				pthread_mutex_lock(&(env->change));
				ft_sleeping(env, c_philo);
			}
			pthread_mutex_lock(&(env->change));
		}
	}
}

void	ft_sleeping(t_env *env, t_philo *c_philo)
{
	int	check_life;

	check_life = 0;
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
}

void	ft_routine_even(t_env *env, t_philo *c_philo)
{
	int	check_life;

	check_life = 0;
				if (ft_getlife(env, c_philo) > env->t_sleep)
				{
					usleep(env->t_sleep);
					if (env->death == 0)
					{
						pthread_mutex_lock(&(env->message));
						ft_philo_write(env, c_philo, "is thinking");
						pthread_mutex_unlock(&(env->message));
						pthread_mutex_lock(&(env->change));
						check_life = ft_check_death(env, c_philo);
						pthread_mutex_unlock(&(env->change));
						if (check_life == 1)
						{
							usleep(ft_getlife(env, c_philo));
							// if (env->death == 0)
							// {
								pthread_mutex_lock(&(env->change));
								env->death = 1;
								//pthread_mutex_unlock(&(env->change));
								pthread_mutex_lock(&(env->message));
								ft_philo_write(env, c_philo, "died");
								usleep(2);
								pthread_mutex_unlock(&(env->message));
								pthread_mutex_unlock(&(env->change));
								return ;
							//}
						}

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
					usleep(2);
					pthread_mutex_unlock(&(env->message));
					pthread_mutex_lock(&(env->change));
					env->death = 1;
					pthread_mutex_unlock(&(env->change));
					return ;
				}
			}
		}
		else
		{
			printf("life left de %d: %lu\n", c_philo->num_p, ft_getlife(env, c_philo));
			usleep(ft_getlife(env, c_philo));
			printf("llego aqui\n");
			if (env->death == 0)
			{
				pthread_mutex_lock(&(env->message));
				ft_philo_write(env, c_philo, "died");
				usleep(2);
				pthread_mutex_unlock(&(env->message));
				pthread_mutex_lock(&(env->change));
				env->death = 1;
				pthread_mutex_unlock(&(env->change));
				return ;
			}
		}
	}
}

void	ft_routine_uneven(t_env *env, t_philo *c_philo)
{
	if ((c_philo->num_p % 2 != 0 && c_philo->num_p != env->n_philos && env->round == 1)
		|| (c_philo->num_p % 2 == 0 && env->round == 2)
			|| (c_philo->num_p == env->n_philos && env->round == 3))
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
			ft_update_round_uneven(env, c_philo);
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
					ft_check_death(env, c_philo);
					if (env->death == 1)
					{
						usleep(ft_getlife(env, c_philo));
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
		

