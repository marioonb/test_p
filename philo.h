/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelorge <mbelorge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 19:24:08 by mbelorge          #+#    #+#             */
/*   Updated: 2021/07/16 20:44:38 by mbelorge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <errno.h>

typedef enum s_action
{
	TAKE_FORK_L,
	TAKE_FORK_R,
	EAT,
	SLEEP,
	THINK,
	DEAD,
}				t_action;

typedef struct s_time
{
	int	tt_d;
	int	tt_e;
	int	tt_s;
}				t_time;

typedef struct s_philo
{
	int				id;
	int				action;
	int				nb_eat;
	long			start_eat;
	long			start_sleep;
	long			last_eat;
	pthread_mutex_t	*forkr;
	pthread_mutex_t	*forkl;
	t_time			tt;
	int				so_eat;
	int				nb_meal;
	pthread_t		t;
	struct s_prog	*p;
}				t_philo;

typedef struct s_prog
{
	int				nb_philo;
	int				must_eat;
	t_time			time;
	long			start_time;
	t_philo			*philo;
	pthread_mutex_t	*fork;
	pthread_t		death_and_food;
	int				all_eat;
	int				one_death;
	pthread_mutex_t	print;
	int				stop;
}				t_prog;

int		ft_isnumber(char *str);
int		ft_atoi(const char *str);
void	ft_error(int index);
long	current_time(long start);
void	check_parametre(int ac, char **av);
void	fill_parametre(char **av, t_prog *p);
void	init_philosopher(t_prog *p);
void	init_fork(t_prog *p);
void	init_time(t_prog *p);
void	take_fork_and_eat(t_philo *p);
void	end_sleep_and_think(t_philo *p);
void	end_eat_and_sleep(t_philo *p);
void	check_eat_finish2(t_philo *p);
void	check_death(t_prog *p);
void	check_death2(t_philo *p);
void	print_msg(t_philo *p);
void	*action(void *arg);
void	*monitor(void *arg);
void	free_all(t_prog *p);
void	aff(long time, int idd, char *msg);

#endif