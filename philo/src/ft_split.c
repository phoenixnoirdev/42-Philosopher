/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phkevin <phkevin@42luxembourg.lu>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:25:11 by phkevin           #+#    #+#             */
/*   Updated: 2024/02/26 11:25:12 by phkevin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src.h"

/**
 * @brief Libère la mémoire allouée pour un tableau de chaînes de caractères.
 * 
 * Cette fonction parcourt un tableau de chaînes de caractères (terminé par 
 * un pointeur NULL) et libère la mémoire allouée pour chaque chaîne. 
 * Ensuite, elle libère également la mémoire allouée pour le tableau lui-même.
 * 
 * @param str Pointeur vers le tableau de chaînes de caractères à libérer. 
 *            Si le pointeur est `NULL`, la fonction ne fait rien.
 */
void	ft_free_split(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
}

/**
 * @brief Compte le nombre de mots dans une chaîne de caractères.
 * 
 * Cette fonction compte le nombre de mots dans la chaîne `s`, où les mots
 * sont séparés par le caractère `c`. Un mot est défini comme une séquence 
 * de caractères non séparés par `c`. La fonction retourne le nombre total 
 * de mots trouvés. Si la chaîne est vide, la fonction retourne 0.
 * 
 * @param s Chaîne de caractères à analyser.
 * @param c Caractère utilisé comme séparateur de mots.
 * @return Le nombre de mots trouvés dans la chaîne.
 */
static int	ft_countword(char const *s, char c)
{
	int	nb;
	int	i;

	nb = 1;
	i = 1;
	if (s[0] == '\0')
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i - 1] != c)
			nb++;
		i++;
	}
	if (s[i - 1] == c)
		nb--;
	return (nb);
}

/**
 * @brief Extrait un mot d'une chaîne de caractères.
 * 
 * Cette fonction extrait un mot d'une chaîne `s` en commençant à partir de 
 * l'index `start` et se terminant avant le caractère `c`. Le mot extrait est 
 * alloué dynamiquement et retourné. La fonction suppose que `start` est un 
 * indice valide dans la chaîne `s`.
 * 
 * @param s Chaîne de caractères source.
 * @param c Caractère utilisé comme délimiteur pour les mots.
 * @param start Index de départ pour l'extraction du mot.
 * @return Pointeur vers la chaîne contenant le mot extrait, ou `NULL` en 
 *         cas d'échec d'allocation mémoire.
 */
static char	*get_word(char const *s, char c, int start)
{
	char	*res;
	int		i;
	int		si;

	i = 0;
	si = 0;
	while (s[start + si] != '\0' && s[start + si] != c)
		si++;
	res = (char *)malloc((si + 1) * sizeof(char *));
	while (i < si)
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

/**
 * @brief Divise une chaîne de caractères en un tableau de sous-chaînes.
 * 
 * Cette fonction divise la chaîne `s` en plusieurs sous-chaînes, séparées
 * par le caractère `c`. Les sous-chaînes sont allouées dynamiquement et 
 * stockées dans un tableau de chaînes de caractères. La fonction ignore 
 * les délimiteurs au début de la chaîne et après chaque sous-chaîne. Le 
 * tableau résultant est terminé par un pointeur NULL.
 * 
 * @param s Chaîne de caractères à diviser.
 * @param c Caractère utilisé comme délimiteur pour la division.
 * @return Pointeur vers le tableau de sous-chaînes, ou `NULL` en cas 
 *         d'échec d'allocation mémoire ou si `s` est `NULL`.
 */
char	**ft_split(char const *s, char c)
{
	char	**res;
	char	*word;
	int		i;
	int		i_res;

	if (!s)
		return (NULL);
	res = (char **)malloc((ft_countword(s, c) + 1) * sizeof(char *));
	i = 0;
	i_res = 0;
	while (s[i] == c && *s)
		i++;
	while (i_res < ft_countword(s, c))
	{
		word = get_word(s, c, i);
		res[i_res++] = ft_strdup(word);
		i += ft_strlen(word);
		free(word);
		while (s[i] == c)
			i++;
	}
	res[i_res] = NULL;
	return (res);
}
