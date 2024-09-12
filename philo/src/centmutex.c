/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   centmutex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phkevin <phkevin@42luxembourg.lu>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 11:37:32 by phkevin           #+#    #+#             */
/*   Updated: 2024/09/12 13:53:29 by phkevin          ###   Luxembour.lu      */
/*                                                                            */
/* ************************************************************************** */

#include "src.h"

/**
 * @brief Récupère l'état d'arrêt de la simulation.
 * 
 * Cette fonction renvoie la valeur du champ `stop` de la structure `param`. 
 * L'accès à ce champ est protégé par un mutex (`stop_mutex`) pour assurer
 * une lecture sûre dans un environnement multithread.
 * 
 * @param param Pointeur vers la structure contenant les informations globales.
 * @return La valeur de `param->stop`, indiquant l'état d'arrêt.
 */
int	ft_getstop(t_param *param)
{
	int	stop;

	pthread_mutex_lock(&param->stop_mutex);
	stop = param->stop;
	pthread_mutex_unlock(&param->stop_mutex);
	return (stop);
}

/**
 * @brief Vérifie et met à jour le nombre de battements d'un philosophe.
 * 
 * Cette fonction vérifie si le philosophe identifié par l'indice `i` a atteint
 * le nombre de battements maximal défini dans `param->nbeat`. Si ce n'est pas 
 * le cas, elle incrémente `param->philo[i].nbeat`. Le verrou est pris et libéré
 * autour de la vérification pour assurer la cohérence des données partagées.
 *
 * @param param Pointeur vers la structure contenant les informations globales.
 * @param i Indice du philosophe à vérifier.
 * @return 0 si le nombre de battements maximal est atteint, 1 sinon.
 */
int	ft_getnbeat(t_param *param, int i)
{
	if (param->nbeat == 1)
	{
		pthread_mutex_lock(&param->philo[i].mnbeat);
		if (param->philo[i].nbeat >= param->nbeat)
		{
			param->philo[i].nbeat++;
			pthread_mutex_unlock(&param->philo[i].mnbeat);
			return (0);
		}
		pthread_mutex_unlock(&param->philo[i].mnbeat);
	}
	else
	{
		pthread_mutex_lock(&param->philo[i].mnbeat);
		if (param->philo[i].nbeat == param->nbeat)
		{
			param->philo[i].nbeat++;
			pthread_mutex_unlock(&param->philo[i].mnbeat);
			return (0);
		}
		pthread_mutex_unlock(&param->philo[i].mnbeat);
	}
	return (1);
}

/**
 * @brief Incrémente et vérifie si tous les philosophes ont mangé.
 * 
 * Cette fonction incrémente le compteur `alleat`, qui représente le nombre 
 * de philosophes ayant terminé de manger. Si ce nombre atteint le total de 
 * philosophes (`nbphilo`), la simulation est arrêtée en définissant 
 * `param->stop` à 1. Les accès à ces variables partagées sont protégés par 
 * des mutex (`malleat` et `stop_mutex`) pour assurer la synchronisation 
 * des threads.
 * 
 * @param param Pointeur vers la structure contenant les informations globales.
 * @return 0 si tous les philosophes ont mangé, 1 sinon.
 */
int	ft_getalleat(t_param *param)
{
	pthread_mutex_lock(&param->malleat);
	param->alleat++;
	if (param->alleat == param->nbphilo)
	{
		pthread_mutex_unlock(&param->malleat);
		pthread_mutex_lock(&param->stop_mutex);
		param->stop = 1;
		pthread_mutex_unlock(&param->stop_mutex);
		return (0);
	}
	pthread_mutex_unlock(&param->malleat);
	return (1);
}
