/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phkevin <phkevin@42luxembourg.lu>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 11:17:18 by phkevin           #+#    #+#             */
/*   Updated: 2024/08/22 12:10:01 by phkevin          ###   Luxembour.lu      */
/*                                                                            */
/* ************************************************************************** */

#ifndef SRC_H
# define SRC_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdint.h>

/* 
 * Color MSG
 */
# define NOCOLORS " \033[0m "
# define RED " \033[1;31m "
# define GREEN " \033[1;32m "
# define YELLOW " \033[1;33m "
# define BLUE " \033[1;34m "
# define MAGENTA " \033[1;35m "
# define CYAN " \033[1;36m "

/*
 * Message Philosopher
 */
# define TAKE "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIED "died"

/* 
 * Max philo
 */
# define MAXPHILO 200

/*
 * Structure
 */
typedef struct s_philo
{
	int					ref;
	int					nbeat;
	int					lasteat;
	int					stop;
	int					pair;
	pthread_mutex_t		meat;
	pthread_mutex_t		mnbeat;
	pthread_mutex_t		mdeath;
	uint64_t			sleep;
	struct s_param		*params;
}	t_philo;

typedef struct s_param
{
	int				nbphilo;
	int				ttdie;
	int				tteat;
	int				ttsleep;
	int				nbeat;
	int				tthink;
	int				alleat;
	int				cycledef;
	int				stop;
	uint64_t		tstart;
	pthread_t		*pthreads;
	pthread_t		*dthreads;
	pthread_mutex_t	*fork;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	print;
	pthread_mutex_t	malleat;
	t_philo			*philo;
}	t_param;

/*
 * ft_split.c
 */
char		**ft_split(char const *s, char c);
void		ft_free_split(char **str);

/*
 * ft_init.c
 */
void		ft_init(char **argv, int spconf, t_param *param);

/*
 * ft_checkarg.c
 */
void		ft_checkarg(char **argv, int spconf, t_param *param);

/*
 * ft_isdigit.c
 */
int			ft_isdigit(int c);

/*
 * main.c
 */
void		ft_error(char **arg, int spconf, t_param *param);
void		ft_errorarg(char **arg, int spconf, t_param *param);

/*
 * ft_strdup.c
 */
char		*ft_strdup(const char *s);

/*
 * ft_strlen.c
 */
size_t		ft_strlen(const char *str);

/*
 * ft_atoi.c
 */
int			ft_atoi(const char *str);

/*
 * ft_print_info.c
 */
void		ft_print_status(uint64_t time, t_param *param, int ref, int type);

/*
 * ft_time.c
 */
uint64_t	ft_get_time_ms(void);

/*
 * ft_action.c
 */
void		ft_start(t_param *param, int i);
void		mutexforklock(t_param *param, t_philo *philo);
void		mutexforkunlock(t_param *param, t_philo *philo);

/*
 * ft_life.c
 */
void		ft_eating(t_philo *philo, t_param *param);
int			ft_death(t_philo *philo, t_param *param);
void		ft_thinking(t_philo *philo, t_param *param);
void		ft_sleep(t_philo *philo, t_param *param);

/*
 * thread.c
 */
void		*srout(void *arg);
void		*deathrout(void *arg);

/*
 * ft_frees.c
 */
void		ft_freeparam(t_param *param);

/*
 * ft_ispaire.c
 */
int			ft_ispaire(int i);

/*
 * centmutex.c 
 */
int			ft_getstop(t_param *param);
int			ft_getnbeat(t_param *param, int i);
int			ft_getalleat(t_param *param);

#endif