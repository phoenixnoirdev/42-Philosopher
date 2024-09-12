/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phkevin <phkevin@42luxembourg.lu>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:04:16 by phkevin           #+#    #+#             */
/*   Updated: 2024/09/12 13:35:20 by phkevin          ###   Luxembour.lu      */
/*                                                                            */
/* ************************************************************************** */

#include "src.h"

/**
 * @brief Initialise les paramètres de la simulation des philosophes.
 * 
 * Cette fonction configure les paramètres de la simulation en fonction des
 * arguments fournis dans `argv`. Elle initialise le nombre de philosophes,
 * les temps d'attente (manger, dormir, mourir), ainsi que le cycle des repas
 * (optionnel). Si le nombre de cycles de repas est spécifié, `cycledef` est
 * activé. La fonction alloue également la mémoire pour les philosophes,
 * les threads, et les fourchettes, et initialise les mutex nécessaires.
 * 
 * @param argv Tableau d'arguments pour initialiser les paramètres.
 * @param param Pointeur vers la structure `t_param` à initialiser.
 * @param spconf Flag de configuration spécifique en cas d'erreur.
 */
static void	ft_init_param(char **argv, t_param *param, int spconf)
{
	param->nbphilo = ft_atoi(argv[0]);
	param->ttdie = ft_atoi(argv[1]);
	param->tteat = ft_atoi(argv[2]);
	param->ttsleep = ft_atoi(argv[3]);
	param->tthink = ((param->tteat - param->ttsleep) / 10);
	if (argv[4])
	{
		param->nbeat = ft_atoi(argv[4]);
		param->cycledef = 1;
	}
	else
	{
		param->nbeat = 0;
		param->cycledef = 0;
	}
	param->stop = 0;
	param->tstart = ft_get_time_ms();
	param->philo = malloc(param->nbphilo * sizeof(t_philo));
	param->pthreads = malloc(param->nbphilo * sizeof(pthread_t));
	param->fork = malloc(param->nbphilo * sizeof(pthread_mutex_t));
	pthread_mutex_init(&param->stop_mutex, NULL);
	if (param->philo == NULL || param->pthreads == NULL || param->fork == NULL)
		ft_error(argv, spconf, param);
}

/**
 * @brief Définit la parité du philosophe.
 * 
 * Cette fonction assigne la valeur de la parité `pair` à un philosophe donné.
 * Si la parité est égale à 0 (impair), la fonction renvoie 1, sinon elle 
 * renvoie 0 après avoir assigné la valeur `p` à `philo->pair`.
 * 
 * @param philo Pointeur vers la structure du philosophe à modifier.
 * @param p Valeur de la parité à assigner (0 pour impair, autre pour pair).
 * @return 1 si le philosophe est impair, 0 sinon.
 */
static int	ft_setphilpair(t_philo *philo, int p)
{
	if (p == 0)
	{
		philo->pair = p;
		return (1);
	}
	else
		philo->pair = p;
	return (0);
}

/**
 * @brief Initialise les philosophes et leurs paramètres.
 * 
 * Cette fonction configure chaque philosophe avec un identifiant unique, 
 * une parité (pair ou impair) déterminée par `ft_setphilpair()`, et les
 * références nécessaires à leurs structures de données. Elle initialise
 * également plusieurs mutex pour chaque philosophe, afin de protéger l'accès
 * aux données critiques (nombre de repas, dernière fois mangé, état de mort).
 * Enfin, elle vérifie que l'initialisation des fourchettes est réussie et 
 * déclenche une erreur en cas d'échec.
 * 
 * @param argv Tableau d'arguments pour initialiser les philosophes.
 * @param param Pointeur vers la structure globale `t_param` contenant 
 *              les paramètres de la simulation.
 * @param spconf Flag de configuration spécifique en cas d'erreur.
 */
static void	ft_init_philo(char **argv, t_param *param, int spconf)
{
	int	i;
	int	p;

	i = 0;
	p = 0;
	param->alleat = 0;
	param->dthreads = malloc(1 * sizeof(pthread_t));
	pthread_mutex_init(&param->print, NULL);
	pthread_mutex_init(&param->malleat, NULL);
	while (i < param->nbphilo)
	{
		p = ft_setphilpair(&param->philo[i], p);
		param->philo[i].ref = i;
		param->philo[i].nbeat = 0;
		param->philo[i].params = param;
		param->philo[i].lasteat = 0;
		param->philo[i].stop = 0;
		pthread_mutex_init(&param->philo[i].meat, NULL);
		pthread_mutex_init(&param->philo[i].mnbeat, NULL);
		pthread_mutex_init(&param->philo[i].mdeath, NULL);
		if (pthread_mutex_init(&param->fork[i], NULL) != 0)
			ft_error(argv, spconf, param);
		i++;
	}
}

/**
 * @brief Initialise la simulation des philosophes.
 * 
 * Cette fonction effectue les étapes d'initialisation de la simulation, 
 * en commençant par vérifier la validité des arguments avec `ft_checkarg()`. 
 * Si le nombre de philosophes est supérieur à 200, elle déclenche une erreur.
 * Ensuite, elle initialise les paramètres globaux de la simulation via 
 * `ft_init_param()` et configure les philosophes individuels avec 
 * `ft_init_philo()`.
 * 
 * @param argv Tableau d'arguments contenant les paramètres de la simulation.
 * @param spconf Flag de configuration spécifique en cas d'erreur.
 * @param param Pointeur vers la structure globale `t_param` à initialiser.
 */
void	ft_init(char **argv, int spconf, t_param *param)
{
	ft_checkarg(argv, spconf, param);
	if (ft_atoi(argv[0]) > 200)
		ft_errorarg(argv, spconf, param);
	ft_init_param(argv, param, spconf);
	ft_init_philo(argv, param, spconf);
}
