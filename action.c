/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelorge <mbelorge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 19:24:08 by mbelorge          #+#    #+#             */
/*   Updated: 2021/07/16 20:44:38 by mbelorge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork_and_eat(t_philo *p)
{
	pthread_mutex_lock(p->forkr);
	p->action = TAKE_FORK_R;
	print_msg(p);
	if (p->p->nb_philo == 1)
	{	
		while (p->action != DEAD)
		{
			usleep(100);
			continue ;
		}
	}
	else
	{
		pthread_mutex_lock(p->forkl);
		p->action = TAKE_FORK_L;
		print_msg(p);
	}
	p->start_eat = current_time(p->p->start_time);
	p->action = EAT;
	print_msg(p);
	p->nb_meal++;
	usleep(p->tt.tt_e * 1000);
}

void	end_sleep_and_think(t_philo *p)
{
	p->action = THINK;
	print_msg(p);
}

void	end_eat_and_sleep(t_philo *p)
{
	pthread_mutex_unlock(p->forkl);
	pthread_mutex_unlock(p->forkr);
	p->start_sleep = current_time(p->p->start_time);
	p->action = SLEEP;
	print_msg(p);
	usleep(p->tt.tt_s * 1000);
}

void	*action(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (p->id % 2 && p->p->nb_philo != 1)
		usleep(10000);
	while (p->p->one_death == 0 && p->p->all_eat == 0)
	{
		take_fork_and_eat(p);
		end_eat_and_sleep(p);
		end_sleep_and_think(p);
	}
	return ((void *) NULL);
}
