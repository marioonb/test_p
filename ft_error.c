/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelorge <mbelorge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 19:24:08 by mbelorge          #+#    #+#             */
/*   Updated: 2021/07/16 20:44:38 by mbelorge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error(int index)
{
	if (index == 1)
		printf ("Merci d'entrer 4 ou 5 paramètres\n");
	if (index == 2)
		printf("il y a trop de parametres\n");
	if (index == 3)
		printf ("merci d'entrer des paramètres valides\n");
	if (index == 4)
		printf ("erreur de malloc\n");
	if (index == 5)
		printf ("il faut au moins un philosophe\n");
	if (index == 6)
		printf ("merci d'entrer des valeurs supérieurs à 0\n");
	exit (0);
}
