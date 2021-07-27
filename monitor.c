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
	int i;

	i = 0;
	//	dprintf(1, "il check la mort à %ld\n", current_time(p->start_time));
	while (i < p->nb_philo)
	{
		if (p->philo[i].start_eat - p->philo[i].last_eat > p->time.tt_d)
		{

			p->one_death = 1;
			p->philo[i].action = DEAD;
			print_msg(&p->philo[i], " --> monitor death");
			//dprintf(1, "p action dans death est a %d\n", p->philo[i].action);
			//dprintf (1,"%ld : %d died\n", current_time(p->start_time), p->philo[i].id);
			//usleep(100);
		}
	i++;
	}
	//dprintf(1, "%ld : personne n est mort\n", current_time(p->start_time));
	//usleep(100); // permet de laisser 100 micro_sec avant le prochain check

}

void check_eat_finish(t_prog *p)
{
	p->all_eat = 0;
	int cpt = 0;
	int i = 0;
	//dprintf(1, "il check eat_finish à %ld\n", current_time(p->start_time));
	while (i < p->nb_philo)
	{
		if (p->philo[i].nb_meal == p->philo[i].nb_eat)
		//	p->so_eat = 1;
		//if (p->philo[i].so_eat)
		//{
			cpt++;
			//dprintf(1, "oui pour le %d", p->philo[i].id);
		//}
		i++;
	}
	//dprintf(1, "ca entre ?? %d \n", cpt);
	//dprintf (1, "p->must_eat = %d et cp = %d\n", p->must_eat, cpt);
	//if (p->must_eat != 0 && cpt >= p->must_eat)
	//if (p->must_eat != 0 && cpt == p->nb_philo)
	if (cpt == p->nb_philo)
	{
		p->all_eat = 1;
		pthread_mutex_lock(&p->print);
		dprintf(1, "%ld : ", current_time(p->start_time));
		dprintf (1,"Tout le monde a mangé\n");
		//exit (0);
	}
	//usleep(100);
}

void *monitor(void *arg)
{

	t_prog *p = (t_prog *)arg;

	while (p->all_eat != 1 && p->one_death <= 0)
{
	//dprintf(1, "\n----CHECK---\n\n");
		if (p->must_eat != 0)
			check_eat_finish(p);
		check_death(p);
}
	return ((void *) NULL);
}
