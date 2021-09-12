/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelorge <mbelorge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 19:24:08 by mbelorge          #+#    #+#             */
/*   Updated: 2021/07/16 20:44:38 by mbelorge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	sizenum(int n)
{
	int		i;

	i = 0;
	if (n < 0)
		n = n * -1;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*chaine;
	int		nombre;
	int		i;

	i = sizenum(n);
	nombre = n;
	if (n < 0)
	{
		nombre = nombre * -1;
		i = i + 1;
	}
	chaine = malloc(i + 1);
	if (!chaine)
		return (0);
	if (i > 0)
		chaine[i] = '\0';
	while (i-- > 0)
	{
		chaine[i] = nombre % 10 + '0';
		nombre = nombre / 10;
	}
	if (n < 0)
		chaine[0] = '-';
	return (chaine);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		write(1, str + i, 1);
		i++;
	}
}

void	aff(long time, int idd, char *msg)
{
	char	*timec;
	char	*id;

	id = ft_itoa(idd);
	timec = ft_itoa(time);
	ft_putstr(timec);
	write (1, " ", 1);
	ft_putstr(id);
	write (1, " ", 1);
	ft_putstr(msg);
	write (1, "\n", 1);
	free(timec);
	free(id);
}

void	print_msg(t_philo *p)
{
	long	time;
	char	*msg;

	time = current_time(p->p->start_time);
	msg = NULL;
	pthread_mutex_lock(&p->p->print);
	if (p->action == DEAD && p->p->stop != 1)
	{
		aff(time, p->id, "died");
		p->p->stop = 1;
	}
	else if (p->action == TAKE_FORK_L || p->action == TAKE_FORK_R)
		msg = "has taken a fork";
	else if (p->action == THINK)
		msg = "is thinking";
	else if (p->action == SLEEP)
		msg = "is sleeping";
	else if (p->action == EAT)
		msg = "is eating";
	if (p->p->one_death == 0 && p->p->all_eat == 0)
		aff(time, p->id, msg);
	pthread_mutex_unlock (&p->p->print);
}
