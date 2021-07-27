/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelorge <mbelorge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 19:24:08 by mbelorge          #+#    #+#             */
/*   Updated: 2021/07/16 20:44:38 by mbelorge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_philosopher(t_prog *p)
{
	int i;

	i = 0;
	p->philo = malloc(sizeof(t_philo) * p->nb_philo);
	while (i < p->nb_philo)
	{
		p->philo[i].id = i + 1;
		p->philo[i].action = THINK;
		p->philo[i].nb_eat = p->must_eat;
		p->philo[i].so_eat = 0;
		p->philo[i].nb_meal = 0;
		p->philo[i].tt = p->time;
		p->philo[i].start_eat = 0;
		p->philo[i].last_eat = 0;
		p->philo[i].p = p;
		i++;
	}
		i = 0;
	while (i < p->nb_philo)
	{
	//	dprintf (1, "i est egall a %d\n", i);
		if (i == 0)
		{
			p->philo[i].forkr = &p->fork[p->nb_philo - 1];
		}
		else
		{
				p->philo[i].forkr = &p->fork[i - 1];
		}
		p->philo[i].forkl = &p->fork[i];
		i++;
	}
//	essai(p);
}

void init_fork(t_prog *p)
{
	int i;

	i = 0;
	p->fork = malloc(sizeof(int) * p->nb_philo);
	if (!p->fork)
		ft_error(4);
	while (i < p->nb_philo)
	{
	////	dprintf (1, "nombre de philo %d, fork %d\n",p->nb_philo, i);
		pthread_mutex_init(&p->fork[i], NULL);
		i++;
	}
////	dprintf (1, "a fini les init mutex\n");

}

void init_time(t_prog *p)
{
	// seconde en milliseconde --> 1 s = 1000 ms --> seconde * 1000
	// micro seconde en milliseconde --> 1 micro seconde = 0,001 ms --> micro seconde / 1000
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	p->start_time = ((tv.tv_sec * 1000) + tv.tv_usec / 1000);
}
