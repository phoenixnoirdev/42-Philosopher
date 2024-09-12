/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phkevin <phkevin@42luxembourg.lu>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 20:51:56 by phkevin           #+#    #+#             */
/*   Updated: 2024/09/12 14:11:39 by phkevin          ###   Luxembour.lu      */
/*                                                                            */
/* ************************************************************************** */

#include "src.h"

/**
 * @brief Affiche un message indiquant qu'un philosophe a pris une fourchette.
 * 
 * Cette fonction affiche un message lorsque le philosophe (identifié par `ref`)
 * prend une fourchette. Le message inclut l'heure écoulée depuis le début de la
 * simulation et le numéro du philosophe. L'affichage est protégé par un mutex 
 * pour éviter les problèmes de concurrence. Le message n'est affiché que si 
 * la simulation n'est pas arrêtée.
 * 
 * @param param Pointeur vers la structure contenant les paramètres de la 
 * 				simulation, y compris le mutex pour l'affichage (`print`) et 
 * 				l'heure de début de la simulation (`tstart`).
 * @param philo Pointeur vers la structure du philosophe qui prend la 
 * 				fourchette.
 */
static void	printfork(t_param *param, t_philo *philo)
{
	int			ref;
	uint64_t	time;

	time = ft_get_time_ms();
	time = time - param->tstart;
	ref = philo->ref + 1;
	if (ft_getstop(param) == 0)
	{
		pthread_mutex_lock(&param->print);
		printf("%s %lu %d %s%s\n", MAGENTA, time, ref, TAKE, NOCOLORS);
		pthread_mutex_unlock(&param->print);
	}
}

/**
 * @brief Verrouille les mutex des fourchettes pour un philosophe.
 * 
 * Cette fonction verrouille les mutex pour les deux fourchettes nécessaires à 
 * un philosophe pour manger. Les indices des fourchettes sont déterminés par 
 * `fleft` (la fourchette de gauche) et `fright` (la fourchette de droite). 
 * La fonction verrouille d'abord la fourchette avec le plus petit indice pour 
 * éviter les interblocages, affiche un message de prise de fourchette avec 
 * `printfork`, puis introduit une pause de 200 microsecondes avant de 
 * verrouiller la seconde fourchette. Elle affiche également un message pour la 
 * deuxième fourchette.
 * 
 * @param param Pointeur vers la structure contenant les paramètres de la 
 *              simulation, y compris les mutex pour les fourchettes (`fork`).
 * @param philo Pointeur vers la structure du philosophe qui verrouille les 
 *              fourchettes.
 */
void	mutexforklock(t_param *param, t_philo *philo)
{
	int	fleft;
	int	fright;

	fleft = philo->ref;
	fright = (philo->ref + 1) % param->nbphilo;
	if (fleft < fright)
	{
		pthread_mutex_lock(&param->fork[fleft]);
		printfork(param, philo);
		usleep(200);
		pthread_mutex_lock(&param->fork[fright]);
		printfork(param, philo);
	}
	else
	{
		pthread_mutex_lock(&param->fork[fright]);
		printfork(param, philo);
		pthread_mutex_lock(&param->fork[fleft]);
		printfork(param, philo);
	}
}

/**
 * @brief Déverrouille les mutex des fourchettes pour un philosophe.
 * 
 * Cette fonction déverrouille les mutex pour les deux fourchettes utilisées 
 * par un philosophe après avoir mangé. Les indices des fourchettes sont 
 * déterminés par `fleft` (la fourchette de gauche) et `fright` (la fourchette 
 * de droite). La fonction déverrouille les fourchettes dans l'ordre inverse de 
 * leur verrouillage pour éviter les problèmes de concurrence.
 * 
 * @param param Pointeur vers la structure contenant les paramètres de la 
 *              simulation, y compris les mutex pour les fourchettes (`fork`).
 * @param philo Pointeur vers la structure du philosophe qui déverrouille les 
 *              fourchettes.
 */
void	mutexforkunlock(t_param *param, t_philo *philo)
{
	int	fleft;
	int	fright;

	fleft = philo->ref;
	fright = (philo->ref + 1) % param->nbphilo;
	if (fleft < fright)
	{
		pthread_mutex_unlock(&param->fork[fright]);
		pthread_mutex_unlock(&param->fork[fleft]);
	}
	else
	{
		pthread_mutex_unlock(&param->fork[fleft]);
		pthread_mutex_unlock(&param->fork[fright]);
	}
}

/**
 * @brief Simule le comportement d'un seul philosophe pour un test.
 * 
 * Cette fonction simule le comportement d'un seul philosophe en affichant un
 * message pour indiquer qu'il a pris une fourchette, puis attend un délai de
 * mort (`ttdie`). Après ce délai, elle affiche un message indiquant que le
 * philosophe est mort. Les messages affichés incluent l'heure écoulée depuis
 * le début de la simulation.
 * 
 * @param param Pointeur vers la structure contenant les paramètres de la 
 *              simulation, y compris le délai de mort (`ttdie`) et l'heure de
 *              début de la simulation (`tstart`).
 */
static void	ft_onephilo(t_param *param)
{
	uint64_t	time;

	time = ft_get_time_ms();
	time = time - param->tstart;
	pthread_mutex_lock(&param->print);
	printf("%s %lu %d %s%s\n", MAGENTA, time, 1, TAKE, NOCOLORS);
	pthread_mutex_unlock(&param->print);
	usleep(param->ttdie * 1000);
	time = ft_get_time_ms();
	time = time - param->tstart;
	pthread_mutex_lock(&param->print);
	printf("%s %lu %d %s%s\n", RED, time, 1, DIED, NOCOLORS);
	pthread_mutex_unlock(&param->print);
}

/**
 * @brief Démarre la simulation des philosophes.
 * 
 * Cette fonction initialise et démarre les threads pour les philosophes et
 * le thread de surveillance de la mort. Si le nombre de philosophes est égal
 * à 1, elle simule directement le comportement du seul philosophe en appelant
 * `ft_onephilo()`. Sinon, elle crée un thread pour chaque philosophe en 
 * utilisant `srout` et un thread pour la surveillance de la mort avec 
 * `deathrout`. Après la création des threads, elle attend la fin du thread de 
 * surveillance de la mort puis attend la fin de tous les threads des 
 * philosophes.
 * 
 * @param param Pointeur vers la structure contenant les paramètres de la 
 *              simulation, y compris les threads des philosophes (`pthreads`) 
 *              et le thread de surveillance de la mort (`dthreads`).
 * @param i Variable utilisée pour itérer sur les philosophes.
 */
void	ft_start(t_param *param, int i)
{
	if (param->nbphilo == 1)
		ft_onephilo(param);
	else
	{
		i = 0;
		while (i < param->nbphilo)
		{
			pthread_create(&param->pthreads[i], NULL, srout, &param->philo[i]);
			i++;
		}
		pthread_create(param->dthreads, NULL, deathrout, param);
		pthread_join(*param->dthreads, NULL);
		i = 0;
		while (i < param->nbphilo)
		{
			pthread_join(param->pthreads[i], NULL);
			i++;
		}
	}
}
