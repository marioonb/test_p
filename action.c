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

void take_fork_and_eat(t_philo *p)
{
//		if (p->id % 2){
		pthread_mutex_lock(p->forkr);
		p->action = TAKE_FORK_L;
		print_msg(p,  " --->take fork");
		//dprintf (1,"%ld %d has taken a fork d %p\n", current_time(p->p->start_time), p->id, p->forkr);//}
		pthread_mutex_lock(p->forkl);
		p->action = TAKE_FORK_R;
		print_msg(p, " --->take fork");
		//dprintf (1,"%ld %d has taken a fork g %p\n",current_time(p->p->start_time), p->id, p->forkl);
//		dprintf(1,"%ld %d a pris les fourchettes\n", current_time(p->p->start_time), p->id);
//		}
//		else {
//		//usleep(800);
//		pthread_mutex_lock(p->forkr);
//		p->action = TAKE_FORK_R;
//		print_msg(p, " --->take fork" );
//		//dprintf (1,"%ld %d a pris la fourchette gauche %p\n",current_time(p->p->start_time), p->id, p->forkl);
//		pthread_mutex_lock(p->forkl);
//		p->action = TAKE_FORK_L;
//		print_msg(p, " --->take fork" );
//		//dprintf (1,"%ld %d a pris la fourchette droite %p\n", current_time(p->p->start_time), p->id, p->forkr);//}
//		}
		p->last_eat = p->start_eat;
		p->start_eat = current_time(p->p->start_time); // 205
		p->action = EAT;
		//check_death2(p);
		////usleep(100);
		print_msg(p,  " --->take fork");
		//dprintf (1, "%ld %d is eating il commence donc a nanger a %ld\n",current_time(p->p->start_time), p->id, p->start_eat);
		usleep(p->tt.tt_e * 1000);
}

void end_sleep_and_think(t_philo *p)
{
	p->action = THINK;
	//dprintf (1,"%ld %d is thinking\n",current_time(p->p->start_time), p->id);
	print_msg(p,  " --->sleep");
}

void end_eat_and_sleep(t_philo *p)
{
	pthread_mutex_unlock(p->forkl);
////	dprintf (1,"%ld : le philo %d rend la fourchette droite\n",  current_time(p->p->start_time), p->id);
//	write(1, "FR\n", 3);
	pthread_mutex_unlock(p->forkr);
////	dprintf (1,"%ld : le philo %d rend la fourchette gauche\n",current_time(p->p->start_time), p->id);
//	write(1, "FD\n", 3);
	p->start_sleep = current_time(p->p->start_time);
	p->action = SLEEP;
	print_msg(p,  " --->end eat");
	//dprintf(1, "%ld %d is sleeping\n", current_time(p->p->start_time), p->id);

	p->nb_meal++;
	//if (p->nb_meal == p->nb_eat)
	//{
	//	p->so_eat = 1;
	//	dprintf(1, "so eat pour %d\n", p->id);
	//}
	usleep(p->tt.tt_s * 1000);
//	dprintf(1, "nb eat %d\n", p->nb_meal);

//	usleep(p->tt.tt_s * 1000);
	//p->nb_meal++;
	//dprintf (1, "le nombre de meal est a %d et le nombre de eat est a %d\n", p->nb_meal, p->nb_eat);

}

void *action(void *arg)
{
	t_philo *p = (t_philo *)arg;

	if (p->id % 2 && p->p->nb_philo != 1)
		usleep(p->tt.tt_e * 1000);
//	while (p->action != DEAD)
	while (p->p->one_death != 1)
	{
		//dprintf(1, "%ld : relaunch %d\n", current_time(p->p->start_time), p->id);
		//dprintf(1,"p one death est a %d\n", p->p->one_death);
		take_fork_and_eat(p);
		end_eat_and_sleep(p);
		end_sleep_and_think(p);
		//usleep(100);
	}
	return ((void *) NULL);

}
