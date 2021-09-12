/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelorge <mbelorge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 19:24:08 by mbelorge          #+#    #+#             */
/*   Updated: 2021/07/16 20:44:38 by mbelorge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_mutex(t_prog *p)
{
	int	i;

	i = 0;
	if (pthread_mutex_destroy(&p->print) == EBUSY)
	{
		pthread_mutex_unlock(&p->print);
		pthread_mutex_destroy(&p->print);
	}
	while (i < p->nb_philo)
	{
		if (pthread_mutex_destroy(&p->fork[i]) == EBUSY)
		{
			pthread_mutex_unlock(&p->fork[i]);
			pthread_mutex_destroy(&p->fork[i]);
		}
		i++;
	}
	if (p->fork)
		free(p->fork);
}

void	free_philo(t_prog *p)
{
	if (p->philo)
		free(p->philo);
}

void	free_all(t_prog *p)
{
	free_philo(p);
	free_mutex(p);
}
