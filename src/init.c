/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proche-c <proche-c@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2022/01/25 12:11:31 by proche-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	ft_gettime(void)
{
	unsigned long	result;
	struct timeval	time;

	gettimeofday(&time, NULL);
	result = time.tv_sec * 1000000 + time.tv_usec;
	return (result);
}

int 	ft_init_env(int ac, char **args, t_env *env)
{
	env->n_philos = ft_atoi(args[1]);
	env->t_die = ft_atoi(args[2]) * 1000;
	env->t_eat = ft_atoi(args[3]) * 1000;
	env->t_sleep = ft_atoi(args[4]) * 1000;
	env->meals = 0;
	env->n_meals = 0;
	env->flag = 0;
	env->philo = malloc(sizeof(t_philo) * env->n_philos);
	if (!env->philo)
		return (1);
	env->forks = malloc(sizeof(pthread_mutex_t) * env->n_philos);
	if (!env->forks)
	{
		free(env->philo);
		return (1);
	}
	if (ac == 6)
	{
		env->meals = 1;
		env->n_meals = ft_atoi(args[5]);
	}
	return (0);
}

int	ft_init_philos(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->n_philos)
	{
		env->philo[i].num_p = i + 1;
		env->philo[i].m_eaten = 0;
		env->philo[i].fork_1 = i;
		if (i != env->n_philos - 1)
			env->philo[i].fork_2 = i + 1;
		else
			env->philo[i].fork_2 = 0;
		env->philo[i].env = env;
		printf("philo %d init\n", env->philo[i].num_p);
		i++;
	}
	return (0);
}

int	ft_init_forks(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->n_philos)
	{
		if (pthread_mutex_init(&(env->forks[i]), NULL))
			return (1);
		printf("fork %d init\n", i + 1);
		i++;
	}
	if (pthread_mutex_init(&(env->message), NULL))
		return (1);
	if (pthread_mutex_init(&(env->change), NULL))
		return (1);
	write(1, "message init\n", 13);
	return (0);
}

int	ft_init(int ac, char **args, t_env *env)
{
	if (ft_init_env(ac, args, env) != 0)
		return (1);
	if (ft_init_philos(env) != 0)
	{
		ft_free_env(env);
		return (1);
	}
	if (ft_init_forks(env) != 0)
	{
		ft_free_env(env);
		return (1);
	}
	return (0);
}
