
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelorge <mbelorge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 19:24:08 by mbelorge          #+#    #+#             */
/*   Updated: 2021/07/16 20:44:38 by mbelorge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



int main(int ac, char **av)
{
	t_prog p;
	int i = 0;

	check_parametre(ac, av);
	init_time(&p);
	fill_parametre(av, &p);
	init_fork(&p);
	init_philosopher(&p);
	while (i < p.nb_philo)
	{
		i++;
	}
	i = 0;
	pthread_mutex_init(&p.print, NULL);
	pthread_create(&p.death_and_food, NULL, monitor, &p);
//	pthread_detach(p.death_and_food);
while (i < p.nb_philo)
	{

		pthread_create(&p.philo[i].t, NULL, action, &p.philo[i]);
		//pthread_detach(p.philo[i].t);
		//pthread_join(p.philo[i].t, NULL); // si je le laisse il fait thread par thread
		i++;
	}
	pthread_join (p.death_and_food, NULL);
	i = 0;
	while (i < p.nb_philo)
	{
		pthread_join(p.philo[i].t, NULL);
		i++;
	}
	return(0);
}
