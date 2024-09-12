/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phkevin <phkevin@42luxembourg.lu>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:41:11 by phkevin           #+#    #+#             */
/*   Updated: 2024/09/11 11:27:49 by phkevin          ###   Luxembour.lu      */
/*                                                                            */
/* ************************************************************************** */

#include "src.h"

/**
 * @brief Calcule la longueur d'une chaîne de caractères.
 * 
 * Cette fonction parcourt la chaîne de caractères `str` jusqu'à ce qu'elle
 * rencontre le caractère nul (`'\0'`). Elle retourne le nombre de caractères
 * dans la chaîne, sans inclure le caractère nul de fin.
 * 
 * @param str Pointeur vers la chaîne de caractères dont la longueur est à 
 *            déterminer.
 * @return La longueur de la chaîne de caractères.
 */
size_t	ft_strlen(const char *str)
{
	size_t	nb;

	nb = 0;
	while (*str != '\0')
	{
		str++;
		nb++;
	}
	return (nb);
}
