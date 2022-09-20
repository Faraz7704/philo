/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:39:23 by fkhan             #+#    #+#             */
/*   Updated: 2022/09/20 21:27:31 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define PURPLE "\033[0;35m"
# define GREEN "\033[0;32m"
# define BLUE "\033[0;34m"
# define RED "\033[0;31m"
# define CYAN "\033[0;36m"
# define ORANGE "\033[0;33m"

typedef enum e_state
{
	START,
	TAKING_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED,
	FINISHED,
}	t_state;

typedef struct s_thdata
{
	struct s_pinfo	*pinfo;
	struct s_philo	*philo;
}	t_thdata;

typedef struct s_mutex
{
	pthread_mutex_t	mutex;
	int				status;
}	t_mutex;

typedef struct s_philo
{
	pthread_t		thid;
	size_t			id;
	size_t			meals;
	t_mutex			lfork;
	t_mutex			*rfork;
	t_state			state;
	int				(*action)(struct s_pinfo *pinfo, struct s_philo *philo);
	size_t			createdt;
	size_t			last_eatt;
}	t_philo;

typedef struct s_pinfo
{
	size_t			amount;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			amount_to_eat;
	t_mutex			write;
	t_mutex			quit;
}	t_pinfo;

// routine
void			*philo_routine(void *data);

// logger
void			log_philo(t_pinfo *info, t_philo *philo);

// philo_states
int				pstate_start(t_pinfo *pinfo, t_philo *philo);
int				pstate_takeforks(t_pinfo *pinfo, t_philo *philo);
int				pstate_eat(t_pinfo *pinfo, t_philo *philo);
int				pstate_sleep(t_pinfo *pinfo, t_philo *philo);
int				pstate_think(t_pinfo *pinfo, t_philo *philo);
int				pstate_died(t_pinfo *pinfo, t_philo *philo);
int				pstate_finished(t_pinfo *pinfo, t_philo *philo);

// philo_state_control
int				is_pstate_valid(t_pinfo *pinfo, t_philo *philo);
int				pstate_transition(t_pinfo *pinfo, t_philo *philo,
					t_state next_state);

// philo_utils
size_t			philo_currt(t_philo *philo);

// mutex
int				mutex_init(t_mutex *mutex_obj);
int				mutex_trylock(t_mutex *mutex_obj);
void			mutex_lock(t_mutex *mutex_obj);
void			mutex_unlock(t_mutex *mutex_obj);
int				mutex_destroy(t_mutex *mutex_obj);

// init
t_pinfo			*init_pinfo(size_t *params, int size);
t_thdata		*init_thdata(t_pinfo *pinfo, t_philo *philo);
t_philo			*init_philo(t_pinfo *pinfo);

// parse_arg
size_t			*parse_arg(char **av, int size);

// utils
int				ft_atol(const char *str, size_t *dst);
size_t			ft_get_time(void);
void			ft_usleep(size_t ms);

#endif