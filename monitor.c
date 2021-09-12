/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelorge <mbelorge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 19:24:08 by mbelorge          #+#    #+#             */
/*   Updated: 2021/07/16 20:44:38 by mbelorge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_death(t_prog *p)
{
	int	i;

	i = 0;
	while (i < p->nb_philo)
	{
		if (current_time(p->start_time) - p->philo[i].start_eat > p->time.tt_d)
		{
			p->philo[i].action = DEAD;
			p->one_death ++;
			print_msg(&p->philo[i]);
		}
		i++;
	}
	usleep(100);
}

void	check_eat_finish(t_prog *p)
{
	int	cpt;
	int	i;

	p->all_eat = 0;
	cpt = 0;
	i = 0;
	while (i < p->nb_philo)
	{
		if (p->philo[i].nb_meal >= p->philo[i].nb_eat)
			cpt++;
		i++;
	}
	if (cpt == p->nb_philo)
	{
		p->all_eat = 1;
		pthread_mutex_lock(&p->print);
		aff(current_time(p->start_time), p->must_eat,
			"minimal meal eating by all philosopher");
		pthread_mutex_unlock(&p->print);
	}
}

void	*monitor(void *arg)
{
	t_prog	*p;

	p = (t_prog *)arg;
	while (p->all_eat != 1 && p->one_death <= 0)
	{
		if (p->must_eat != 0)
			check_eat_finish(p);
		check_death(p);
	}
	return ((void *) NULL);
}
