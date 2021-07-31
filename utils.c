/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelorge <mbelorge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 19:24:08 by mbelorge          #+#    #+#             */
/*   Updated: 2021/07/16 20:44:38 by mbelorge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

void print_msg(t_philo *p, char *c)
{

long time;

time = current_time(p->p->start_time);

char *msg = NULL;
//usleep(100);
pthread_mutex_lock(&p->p->print);
if (p->action == DEAD)
	dprintf (1,"%ld : %d died %s\n", time, p->id, c);
	//msg = "; died";
else if (p->action == TAKE_FORK_L || p->action == TAKE_FORK_R)
	//dprintf (1,"%ld %d take a fork %s, nb %d\n", time, p->id, c, p->action);
	msg = "take a fork";
else if (p->action == THINK)
	//dprintf (1,"%ld %d is thinking %s\n",time, p->id, c);
	msg = " : is thinking";
else if (p->action == SLEEP)
	//dprintf(1, "%ld %d is sleeping %s\n", time, p->id, c);
	msg = " : is sleeping";
else if (p->action == EAT)
	//dprintf (1, "%ld %d is eating %s\n", time, p->id, c);
	msg = "is eating ";
//else
//	dprintf(1, "%ld %d il fait autre chose %s\n", time, p->id, c);
//if (p->p->one_death == 0)

//if (p->action != DEAD && p->p->all_eat == 0)
if (p->p->one_death == 0)// && p->action != DEAD && p->p->all_eat == 0)
	dprintf (1, "%ld %d %s %s\n", time, p->id, msg, c);
	pthread_mutex_unlock(&p->p->print);
//else
//	dprintf(1, "%ld il a pas unlock a cause de %d qui est a %d %s\n", time, p->id, p->action, c);

}

int		ft_isnumber(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0' && str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int		ft_atoi(const char *str)
{
	int i;
	int a;
	int nb;

	i = 0;
	a = 1;
	nb = 0;
	while (str[i] == '\t' || str[i] == '\v' || str[i] == '\n' ||
		str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			a = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = (nb * 10) + (str[i] - 48);
		i++;
	}
	return (nb * a);
}

void check_parametre(int ac, char **av)
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

long current_time(long start)
{
	struct timeval	tv;
	long			time;

	gettimeofday(&tv, NULL);
	time = ((tv.tv_sec * 1000) + tv.tv_usec / 1000);
	return (time - start);

}
void fill_parametre(char **av, t_prog *p)
{
	p->nb_philo = ft_atoi(av[1]);
	if (p->nb_philo <= 0)
		ft_error(5);
	p->time.tt_d = ft_atoi(av[2]);
	////dprintf(1, "time to die est a %d\n", p->time.tt_d);
	p->time.tt_e = ft_atoi(av[3]);
	p->time.tt_s = ft_atoi(av[4]);
	if (av[5])
	{
		p->must_eat = ft_atoi(av[5]);
		if (p->must_eat <= 0)
			ft_error(6);
	}
	else
		p->must_eat = 0;
	if (p->time.tt_d <= 0 || p->time.tt_e <= 0 || p->time.tt_s <= 0)
		ft_error(6);
	p->one_death = 0;
	p->all_eat = 0;
}
