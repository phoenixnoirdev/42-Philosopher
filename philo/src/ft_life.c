/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_life.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phkevin <phkevin@42luxembourg.lu>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:37:22 by phkevin           #+#    #+#             */
/*   Updated: 2024/09/12 14:48:23 by phkevin          ###   Luxembour.lu      */
/*                                                                            */
/* ************************************************************************** */

#include "src.h"

/**
 * @brief Fait dormir un philosophe pendant une durée spécifiée.
 * 
 * Cette fonction affiche un message indiquant que le philosophe (identifié
 * par `ref`) est en train de dormir, puis met le fil d'exécution en veille
 * pendant une durée déterminée par `ttsleep`. Le message est protégé par un 
 * mutex pour éviter les problèmes de concurrence lors de l'affichage. La durée
 * de sommeil est calculée en microsecondes en utilisant `usleep()`.
 * 
 * @param philo Pointeur vers la structure du philosophe qui dort.
 * @param param Pointeur vers la structure contenant les paramètres de la 
 *              simulation, y compris la durée de sommeil (`ttsleep`) et 
 *              l'heure de début de la simulation (`tstart`).
 */
void	ft_sleep(t_philo *philo, t_param *param)
{
	uint64_t	time;
	int			ref;

	time = ft_get_time_ms();
	time = time - param->tstart;
	ref = philo->ref + 1;
	if (ft_getstop(param) == 0)
	{
		pthread_mutex_lock(&param->print);
		printf("%s %lu %d %s%s\n", GREEN, time, ref, SLEEP, NOCOLORS);
		pthread_mutex_unlock(&param->print);
	}
	usleep(param->ttsleep * 1000);
}

/**
 * @brief Indique qu'un philosophe est en train de penser.
 * 
 * Cette fonction affiche un message indiquant que le philosophe (identifié
 * par `ref`) est en train de penser, puis met le fil d'exécution en veille
 * pendant une durée déterminée par `tthink`. Le message est protégé par un 
 * mutex pour éviter les problèmes de concurrence lors de l'affichage. La durée
 * de sommeil est calculée en microsecondes en utilisant `usleep()`.
 * 
 * @param philo Pointeur vers la structure du philosophe qui pense.
 * @param param Pointeur vers la structure contenant les paramètres de la 
 *              simulation, y compris la durée de réflexion (`tthink`) et 
 *              l'heure de début de la simulation (`tstart`).
 */
void	ft_thinking(t_philo *philo, t_param *param)
{
	uint64_t	time;

	time = ft_get_time_ms();
	time = time - param->tstart;
	if (ft_getstop(param) == 0)
	{
		pthread_mutex_lock(&param->print);
		printf("%s %lu %d %s%s\n", CYAN, time, philo->ref + 1, THINK, NOCOLORS);
		pthread_mutex_unlock(&param->print);
	}
	if (param->tthink > 0)
		usleep(param->tthink * 1000);
}

/**
 * @brief Indique qu'un philosophe est en train de manger.
 * 
 * Cette fonction affiche un message indiquant que le philosophe (identifié
 * par `ref`) est en train de manger, puis met le fil d'exécution en veille
 * pendant une durée déterminée par `tteat`. Le message est protégé par un 
 * mutex pour éviter les problèmes de concurrence lors de l'affichage. La 
 * fonction met également à jour le temps du dernier repas (`lasteat`) et le 
 * nombre de repas (`nbeat`) du philosophe. Après avoir mis à jour ces valeurs,
 * elle appelle `mutexforkunlock()` pour libérer les fourchettes.
 * 
 * @param philo Pointeur vers la structure du philosophe qui mange.
 * @param param Pointeur vers la structure contenant les paramètres de la 
 *              simulation, y compris la durée du repas (`tteat`) et 
 *              l'heure de début de la simulation (`tstart`).
 */
void	ft_eating(t_philo *philo, t_param *param)
{
	uint64_t	time;

	time = ft_get_time_ms();
	time = time - param->tstart;
	if (ft_getstop(param) == 0)
	{
		pthread_mutex_lock(&param->print);
		printf("%s %lu %d %s%s\n", YELLOW, time, philo->ref + 1, EAT, NOCOLORS);
		pthread_mutex_unlock(&param->print);
	}
	pthread_mutex_lock(&philo->meat);
	philo->lasteat = time;
	pthread_mutex_unlock(&philo->meat);
	pthread_mutex_lock(&philo->mnbeat);
	philo->nbeat++;
	pthread_mutex_unlock(&philo->mnbeat);
	usleep(param->tteat * 1000);
	mutexforkunlock(param, philo);
}

/**
 * @brief Vérifie si un philosophe est mort.
 * 
 * Cette fonction calcule le temps écoulé depuis le dernier repas du philosophe
 * et détermine si ce temps dépasse le délai de mort (`ttdie`). Si le philosophe
 * est considéré comme mort et que la simulation n'est pas encore arrêtée, la 
 * fonction marque la simulation comme terminée en mettant `stop` à 1, affiche
 * un message de décès pour le philosophe, et retourne 0. Sinon, elle retourne 
 * 1.
 * 
 * @param philo Pointeur vers la structure du philosophe à vérifier.
 * @param param Pointeur vers la structure contenant les paramètres de la 
 *              simulation, y compris le délai de mort (`ttdie`) et 
 *              l'heure de début de la simulation (`tstart`).
 * @return 0 si le philosophe est mort et la simulation est arrêtée, 1 sinon.
 */
int	ft_death(t_philo *philo, t_param *param)
{
	uint64_t	time;
	int			conttime;

	time = (ft_get_time_ms() - param->tstart);
	pthread_mutex_lock(&philo->meat);
	conttime = time - philo->lasteat;
	pthread_mutex_unlock(&philo->meat);
	if (conttime > param->ttdie && ft_getstop(param) == 0)
	{
		pthread_mutex_lock(&param->stop_mutex);
		param->stop = 1;
		pthread_mutex_unlock(&param->stop_mutex);
		pthread_mutex_lock(&param->print);
		printf("%s %lu %d %s%s\n", RED, time, philo->ref + 1, DIED, NOCOLORS);
		pthread_mutex_unlock(&param->print);
		return (0);
	}
	return (1);
}
