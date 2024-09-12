/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phkevin <phkevin@42luxembourg.lu>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:09:14 by phkevin           #+#    #+#             */
/*   Updated: 2024/09/12 14:03:21 by phkevin          ###   Luxembour.lu      */
/*                                                                            */
/* ************************************************************************** */

#include "src.h"

/**
 * @brief Routine d'exécution des philosophes (pair/impair).
 * 
 * Cette fonction définit le comportement des philosophes en fonction de 
 * leur parité. Si le philosophe est impair, il attend avant de commencer 
 * à manger pour éviter des conflits d'accès aux fourchettes. Elle utilise 
 * un mutex pour protéger la mise à jour de l'heure du dernier repas. Ensuite, 
 * tant que la simulation n'est pas arrêtée, le philosophe suit un cycle de 
 * manger, dormir, et penser en utilisant les fonctions correspondantes.
 * 
 * @param arg Pointeur vers la structure `t_philo` du philosophe courant.
 * @return NULL lorsque la simulation est terminée.
 */
void	*srout(void *arg)
{
	t_philo	*philo;
	t_param	*param;

	philo = (t_philo *)arg;
	param = philo->params;
	pthread_mutex_lock(&philo->meat);
	if (philo->pair == 0)
	{
		usleep(param->ttsleep * 1000);
		philo->lasteat = ft_get_time_ms() - param->tstart + param->ttdie;
		pthread_mutex_unlock(&philo->meat);
	}
	else
	{
		philo->lasteat = ft_get_time_ms() - param->tstart;
		pthread_mutex_unlock(&philo->meat);
	}
	while (ft_getstop(param) == 0)
	{
		mutexforklock(param, philo);
		ft_eating(philo, param);
		ft_sleep(philo, param);
		ft_thinking(philo, param);
	}
	return (NULL);
}

/**
 * @brief Routine de surveillance de la mort des philosophes.
 * 
 * Cette fonction surveille en continu si un philosophe meurt ou si tous 
 * les philosophes ont terminé leurs cycles de repas. Elle commence par
 * un délai défini par `ttdie` avant d'entrer dans une boucle qui vérifie 
 * la condition de mort pour chaque philosophe via `ft_death()`. Si 
 * tous les philosophes ont terminé de manger, la fonction arrête la 
 * simulation. Les vérifications de cycles sont également effectuées si 
 * `cycledef` est activé.
 * 
 * @param arg Pointeur vers la structure `t_param` passée en argument.
 * @return NULL en cas d'arrêt de la simulation.
 */
void	*deathrout(void *arg)
{
	int			i;
	t_param		*param;

	param = (t_param *)arg;
	usleep(param->ttdie * 1000);
	while (1)
	{
		i = -1;
		while (++i < param->nbphilo)
		{
			if (ft_death(&param->philo[i], param) == 0)
				return (NULL);
			if (param->cycledef == 1)
				if (ft_getnbeat(param, i) == 0)
					if (ft_getalleat(param) == 0)
						return (NULL);
		}
	}
	return (NULL);
}
