/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkarg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phkevin <phkevin@42luxembourg.lu>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:54:35 by phkevin           #+#    #+#             */
/*   Updated: 2024/09/11 11:35:24 by phkevin          ###   Luxembour.lu      */
/*                                                                            */
/* ************************************************************************** */

#include "src.h"

/**
 * @brief Vérifie la validité des arguments de la ligne de commande.
 * 
 * Cette fonction parcourt les arguments de la ligne de commande (`argv`) et
 * vérifie que chacun est un nombre entier positif. Elle s'assure également que
 * le nombre total d'arguments est soit 4 soit 5. Si un argument est invalide
 * ou si le nombre d'arguments est incorrect, elle appelle `ft_errorarg()` pour
 * gérer l'erreur.
 * 
 * @param argv Tableau des arguments de la ligne de commande.
 * @param spconf Configuration spécifique pour la gestion des erreurs.
 * @param param Pointeur vers la structure des paramètres de la simulation.
 */
void	ft_checkarg(char **argv, int spconf, t_param *param)
{
	int	i_argc;
	int	i;

	i_argc = 0;
	while (argv[i_argc])
	{
		if (!(ft_atoi(argv[i_argc])))
			ft_errorarg(argv, spconf, param);
		i = 0;
		while (argv[i_argc][i])
		{
			if (!(argv[i_argc][i] >= 48 && argv[i_argc][i] <= 57))
				ft_errorarg(argv, spconf, param);
			i++;
		}
		i_argc++;
	}
	if (!(i_argc == 4 || i_argc == 5))
		ft_errorarg(argv, spconf, param);
}
