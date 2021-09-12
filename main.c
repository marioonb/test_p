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

void	init_all(t_prog *p)
{
	p->nb_philo = 0;
	p->must_eat = 0;
	p->start_time = 0;
	p->philo = NULL;
	p->fork = NULL;
	p->death_and_food = 0;
	p->all_eat = 0;
	p->one_death = 0;
	p->stop = 0;
}

void	check_parametre(int ac, char **av)
{
	if (ac < 5)
		ft_error(1);
	if (ac > 6)
		ft_error(2);
	av++;
	while (*av)
	{
		if (ft_isnumber(av[0]) != 1)
			ft_error(3);
		av ++;
	}
}

void	initialisation(t_prog *p, char **av)
{
	init_all(p);
	init_time(p);
	fill_parametre(av, p);
	init_fork(p);
	init_philosopher(p);
}

int	main(int ac, char **av)
{
	t_prog	p;
	int		i;

	i = 0;
	check_parametre(ac, av);
	initialisation(&p, av);
	while (i < p.nb_philo)
		i++;
	i = 0;
	pthread_mutex_init(&p.print, NULL);
	pthread_create(&p.death_and_food, NULL, monitor, &p);
	while (i < p.nb_philo)
	{
		pthread_create(&p.philo[i].t, NULL, action, &p.philo[i]);
		i++;
	}
	pthread_join (p.death_and_food, NULL);
	i = 0;
	while (i < p.nb_philo)
	{
		pthread_join(p.philo[i].t, NULL);
		i++;
	}
	free_all(&p);
	return (0);
}
