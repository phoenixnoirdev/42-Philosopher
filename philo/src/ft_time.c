/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phkevin <phkevin@42luxembourg.lu>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 19:29:44 by phkevin           #+#    #+#             */
/*   Updated: 2024/09/11 11:27:15 by phkevin          ###   Luxembour.lu      */
/*                                                                            */
/* ************************************************************************** */

#include "src.h"

/**
 * @brief Récupère l'heure actuelle en millisecondes.
 * 
 * Cette fonction utilise `gettimeofday()` pour obtenir l'heure actuelle 
 * sous forme de structure `timeval`, puis convertit cette valeur en 
 * millisecondes. Le temps retourné est une valeur en `uint64_t`, représentant
 * le nombre de millisecondes écoulées depuis l'époque (1er janvier 1970).
 * 
 * @return Le temps actuel en millisecondes.
 */
uint64_t	ft_get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000ULL) + (tv.tv_usec / 1000ULL));
}
