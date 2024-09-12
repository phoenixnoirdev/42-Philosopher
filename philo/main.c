/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phkevin <phkevin@42luxembourg.lu>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:41:13 by phkevin           #+#    #+#             */
/*   Updated: 2024/09/12 13:03:02 by phkevin          ###   Luxembour.lu      */
/*                                                                            */
/* ************************************************************************** */

#include "./src/src.h"

void	ft_error(char **arg, int spconf, t_param *param)
{
	printf("Error\n");
	if (spconf == 1)
		ft_free_split(arg);
	if (param != NULL)
	{
		if (param->philo != NULL)
			free(param->philo);
		if (param->pthreads != NULL)
			free(param->pthreads);
		if (param->dthreads != NULL)
			free(param->dthreads);
		ft_freeparam(param);
		free(param);
	}
	exit(EXIT_FAILURE);
}

void	ft_errorarg(char **arg, int spconf, t_param *param)
{
	printf("Error arg\n");
	if (spconf == 1)
		ft_free_split(arg);
	if (param != NULL)
		free(param);
	exit(EXIT_FAILURE);
}

static void	ft_free(char **arg, t_param *param)
{
	ft_free_split(arg);
	if (param->pthreads != NULL)
		free(param->pthreads);
	if (param->dthreads != NULL)
		free(param->dthreads);
	if (param->philo != NULL)
		free(param->philo);
	free(param);
}

int	main(int argc, char *argv[])
{
	static char	**argsplit = NULL;
	t_param		*param;

	argv++;
	param = (t_param *)malloc(sizeof(t_param));
	if (argc == 2)
	{
		argsplit = ft_split(*argv, ' ');
		ft_init(argsplit, 1, param);
	}
	else if (argc == 5 || argc == 6)
		ft_init(argv, 0, param);
	else
		ft_errorarg(argsplit, 0, param);
	ft_start(param, 0);
	ft_freeparam(param);
	ft_free(argsplit, param);
	return (0);
}
