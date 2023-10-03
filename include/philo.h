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
	int				death;
	int				n_meals;
	int				finish;
	int				round;
	unsigned long	t_start;
	t_philo 		*philo;
	pthread_mutex_t	*forks;
	//int				*bl_forks;
	pthread_mutex_t	message;
	pthread_mutex_t change;
}	t_env;


int			ft_check_parameters(int ac, char **args);
unsigned long	ft_atoi(const char *str);
char		*ft_itoa_p(unsigned long n);
unsigned long	ft_gettime(void);
int			ft_init(int ac, char **args, t_env *env);
int			ft_init_forks(t_env *env);
int			ft_init_philos(t_env *env);
int			ft_init_env(int ac, char **args, t_env *env);
void		ft_free_env(t_env *env);
void 		ft_destroy(t_env *env);
int 		ft_start_threads(t_env *env);
void 		*ft_routine(void *args);
//void 	*ft_routine_uneven(void *args);
void 	*ft_routine_one(void *args);
//int			ft_check_finish(t_env *env, t_philo *c_philo);
int			ft_strlen(char *str);
void		ft_philo_write(t_env *env, t_philo *c_philo, char *str);
void 		ft_get_forks(t_env *env, t_philo *c_philo);
//void 		ft_get_forks_uneven(t_env *env, t_philo *c_philo);
void 		ft_eat(t_env *env, t_philo *c_philo);
void 		ft_sleep(t_env *env, t_philo *c_philo);
//void 		ft_think(t_env *env, t_philo *c_philo);

#endif
