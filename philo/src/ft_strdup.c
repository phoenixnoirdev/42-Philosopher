/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phkevin <phkevin@42luxembourg.lu>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:50:58 by phkevin           #+#    #+#             */
/*   Updated: 2024/09/11 11:28:32 by phkevin          ###   Luxembour.lu      */
/*                                                                            */
/* ************************************************************************** */

#include "src.h"

/**
 * @brief Duplique une chaîne de caractères.
 * 
 * Cette fonction alloue dynamiquement de la mémoire pour une nouvelle chaîne 
 * de caractères, puis copie le contenu de la chaîne source `s` dans cette 
 * nouvelle chaîne. La chaîne dupliquée est terminée par un caractère nul 
 * (`'\0'`). Si l'allocation de mémoire échoue, la fonction retourne `NULL`.
 * 
 * @param s Pointeur vers la chaîne de caractères à dupliquer.
 * @return Pointeur vers la nouvelle chaîne de caractères dupliquée, ou 
 *         `NULL` en cas d'échec de l'allocation mémoire.
 */
char	*ft_strdup(const char *s)
{
	int		index;
	char	*dest;

	dest = (char *) malloc ((ft_strlen(s) + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	index = 0;
	while (s[index] != '\0')
	{
		dest[index] = s[index];
		index++;
	}
	dest[index] = 0;
	return (dest);
}
