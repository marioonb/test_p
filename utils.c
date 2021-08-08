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

/*static int	sizenum(int n)
{
	int		i;

	i = 1;
	if (n < 0)
		n = n * -1;
	while (n /= 10)
		i++;
	return (i);
}

char		*ft_itoa(int n)
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
	if (!(chaine = malloc(i + 1)))
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
}*/

void	print_msg(t_philo *p)
{
	long	time;
	char	*msg;

	time = current_time(p->p->start_time);
	msg = NULL;
	pthread_mutex_lock(&p->p->print);
	if (p->action == DEAD && p->p->one_death <= 1)
		dprintf (1, "%ld %d died\n", time, p->id);
	else if (p->action == TAKE_FORK_L || p->action == TAKE_FORK_R)
		msg = "has taken a fork";
	else if (p->action == THINK)
		msg = "is thinking";
	else if (p->action == SLEEP)
		msg = "is sleeping";
	else if (p->action == EAT)
		msg = "is eating";
	if (p->p->one_death == 0 && p->p->all_eat == 0)
	{	dprintf (1, "%ld %d %s\n", time, p->id, msg);
		//printf("%d\n", p->p->one_death);
	}
	pthread_mutex_unlock (&p->p->print);
}

int	ft_isnumber(char *str)
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

int	ft_atoi(const char *str)
{
	int	i;
	int	a;
	int	nb;

	i = 0;
	a = 1;
	nb = 0;
	while (str[i] == '\t' || str[i] == '\v' || str[i] == '\n'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
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

long	current_time(long start)
{
	struct timeval	tv;
	long			time;

	gettimeofday(&tv, NULL);
	time = ((tv.tv_sec * 1000) + tv.tv_usec / 1000);
	return (time - start);
}
void	fill_parametre(char **av, t_prog *p)
{
	p->nb_philo = ft_atoi(av[1]);
	if (p->nb_philo <= 0)
		ft_error(5);
	p->time.tt_d = ft_atoi(av[2]);
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
