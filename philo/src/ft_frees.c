/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_frees.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phkevin <phkevin@42luxembourg.lu>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:21:36 by phkevin           #+#    #+#             */
/*   Updated: 2024/09/11 11:34:47 by phkevin          ###   Luxembour.lu      */
/*                                                                            */
/* ************************************************************************** */

#include "src.h"

/**
 * @brief Détruit les mutex associés à un philosophe.
 * 
 * Cette fonction détruit les mutex utilisés par un philosophe pour la gestion
 * de l'accès aux ressources partagées, comme le mutex pour la nourriture 
 * (`meat`), le mutex pour le nombre de repas (`mnbeat`), et le mutex pour la 
 * détection de la mort (`mdeath`).
 * 
 * @param philo Pointeur vers la structure du philosophe dont les mutex doivent 
 * être détruits.
 */
static void	ft_freephilo(t_philo *philo)
{
	pthread_mutex_destroy(&philo->meat);
	pthread_mutex_destroy(&philo->mnbeat);
	pthread_mutex_destroy(&philo->mdeath);
}

/**
 * @brief Libère la mémoire et détruit les ressources pour les paramètres de 
 * la simulation.
 * 
 * Cette fonction libère la mémoire allouée pour les philosophes et les f
 * ourchettes, ainsi que les ressources associées comme les mutex. Elle 
 * parcourt le tableau des philosophes, libère chaque philosophe en appelant 
 * `ft_freephilo()`, et détruit les mutex associés aux fourchettes. Enfin, elle 
 * libère les tableaux de fourchettes et détruit les mutex restants pour les 
 * paramètres globaux.
 * 
 * @param param Pointeur vers la structure `t_param` contenant les ressources 
 * à libérer.
 */
void	ft_freeparam(t_param *param)
{
	int	i;

	i = 0;
	while (i < param->nbphilo)
	{
		ft_freephilo(&param->philo[i]);
		pthread_mutex_destroy(&param->fork[i++]);
	}
	free(param->fork);
	pthread_mutex_destroy(&param->stop_mutex);
	pthread_mutex_destroy(&param->print);
	pthread_mutex_destroy(&param->malleat);
}
