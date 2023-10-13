/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proche-c <proche-c@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2022/01/25 12:11:31 by proche-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define DEAD 4

typedef struct s_philo
{
	int				num_p;
	int				m_eaten;
	int				flag;
	int				finish;
	int				eating;
	unsigned long	last_meal;
	int				fork_1;
	int				fork_2;
	pthread_t		id;
	struct s_env	*env;
}	t_philo;

typedef struct s_env
{
	int				n_philos;
	unsigned long	t_die;
	unsigned long	t_eat;
	unsigned long	t_sleep;
	unsigned long	*last_meals;
	int				death;
	int				n_meals;
	int				finish;
	int				round;
	unsigned long	t_start;
	t_philo 		*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	message;
	pthread_mutex_t change;
}	t_env;

/*	checkers	*/
int				ft_check_parameters(int ac, char **args);

/*	clean	*/
void			ft_free_env(t_env *env);
void 			ft_destroy(t_env *env);

/*	init	*/
unsigned long	ft_gettime(void);
int 			ft_init_env(int ac, char **args, t_env *env);
int				ft_init_philos(t_env *env);
int				ft_init_forks(t_env *env);
int				ft_init(int ac, char **args, t_env *env);

/*	philo_one	*/
void 			*ft_routine_one(void *args);
void			ft_die_eating(t_env *env, t_philo *c_philo);

/*	philos_utils	*/
unsigned long	ft_getlife(t_env *env, t_philo *c_philo);
void			ft_philo_write(t_env *env, t_philo *c_philo, char *str);
int				ft_get_left(t_env *env, t_philo *c_philo);
int				ft_get_rigth(t_env *env, t_philo *c_philo);
int			ft_check_death(t_env *env, t_philo *c_philo, int left, int rigth);

/*	philos_even	*/
void			ft_update_round_even(t_env *env, t_philo *c_philo);
void			ft_check_philo_finish(t_env *env, t_philo *c_philo);
void			ft_eat_even(t_env *env, t_philo *c_philo);
void			ft_eat_to_sleep(t_env *env, t_philo *c_philo);
void			ft_sleep_to_think(t_env *env, t_philo *c_philo);
void			ft_thinking(t_env *env, t_philo *c_philo);

/*	philos_uneven	*/
void			ft_update_round_uneven(t_env *env, t_philo *c_philo);
void			ft_eat_uneven(t_env *env, t_philo *c_philo);
void			ft_eat_to_sleep_uneven(t_env *env, t_philo *c_philo);

/*	threads	*/
void 			*ft_routine(void *args);
int 			ft_start_threads(t_env *env);

/*	utils	*/ // 2 static
unsigned long	ft_atoi(const char *str);
int				ft_strlen(char *str);

#endif
