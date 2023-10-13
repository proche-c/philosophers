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

int	ft_check_death(t_env *env, t_philo *c_philo, int left, int rigth)
{
	unsigned long	life;
	unsigned long	time;
	unsigned long	t_rigth;
	unsigned long	t_left;

	time = ft_gettime();
	// printf("\n**** %d *****\n", c_philo->num_p);
	// printf("time: %lu\n", ft_gettime());
	life = ft_getlife(env, c_philo);
	// printf("philo left: %d\n", left);
	// printf("philo rigth: %d\n", rigth);
	if ((env->last_meals[left] + env->t_eat) >= time && (env->last_meals[rigth] + env->t_eat) >= time)
	{
		//printf("los de al lado estan comiendo\n");
		t_left = env->last_meals[left] + env->t_eat - time;
		t_rigth = env->last_meals[rigth] + env->t_eat - time;
		// printf("al de la izquierda le quedan %lu\n", t_left);
		// printf("al de la derecha le quedan %lu\n", t_rigth);
		// printf("a %d le quedan %lu de vida\n", c_philo->num_p, life);
		if (t_left < t_rigth)
		{
			if (life < t_left)
			{
				pthread_mutex_lock(&(env->message));
				//ft_philo_write(env, c_philo, "WILL DIE");
				pthread_mutex_unlock(&(env->message));
				return (1);
			}
		}
		else
		{
			if (life < t_rigth)
			{
				pthread_mutex_lock(&(env->message));
				//ft_philo_write(env, c_philo, "WILL DIE");
				pthread_mutex_unlock(&(env->message));
				return (1);
			}
		}
	}
	return (0);
}
		