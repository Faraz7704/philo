/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:39:23 by fkhan             #+#    #+#             */
/*   Updated: 2022/09/26 21:04:04 by fkhan            ###   ########.fr       */
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

typedef struct s_thsize_t
{
	pthread_mutex_t	mutex;
	size_t			value;
}	t_thsize_t;

typedef struct s_philo
{
	pthread_t		thid;
	size_t			id;
	ssize_t			meals;
	size_t			lfork;
	size_t			rfork;
	size_t			maskout_fork;
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
	ssize_t			amount_to_eat;
	t_thsize_t		*forks;
	t_thsize_t		write;
	t_thsize_t		finish;
	t_thsize_t		quit;
}	t_pinfo;

// routine
int				get_quit_status(t_pinfo *pinfo);
void			*philo_routine(void *data);

// logger
void			log_philo(t_pinfo *info, t_philo *philo,
					char *prefix, char *suffix);
void			log_philo_woid(t_pinfo *info, t_philo *philo,
					char *prefix, char *suffix);

// philo_states
int				pstate_start(t_pinfo *pinfo, t_philo *philo);
int				pstate_takeforks(t_pinfo *pinfo, t_philo *philo);
int				pstate_eat(t_pinfo *pinfo, t_philo *philo);
int				pstate_sleep(t_pinfo *pinfo, t_philo *philo);
int				pstate_think(t_pinfo *pinfo, t_philo *philo);

// thread_size_t
int				thsize_t_init(t_thsize_t *data, size_t value);
void			thsize_t_set(t_thsize_t *data, size_t value);
size_t			thsize_t_get(t_thsize_t *data);
int				thsize_t_destroy(t_thsize_t *data, size_t value);

// philo_exit_states
int				pstate_died(t_pinfo *pinfo, t_philo *philo);
int				pstate_finished(t_pinfo *pinfo, t_philo *philo);

// philo_state_control
int				is_pstate_valid(t_pinfo *pinfo, t_philo *philo);
int				pstate_transition(t_pinfo *pinfo, t_philo *philo,
					t_state next_state);

// philo_utils
size_t			philo_currt(t_philo *philo);
void			set_forks_status(t_pinfo *pinfo, t_philo *philo, size_t value);
int				get_forks_status(t_pinfo *pinfo, t_philo *philo);
void			update_meals(t_pinfo *pinfo, t_philo *philo);

// init
t_pinfo			*init_pinfo(size_t *params, int size);
t_thdata		*init_thdata(t_pinfo *pinfo, t_philo *philo);
t_philo			*init_philo(t_pinfo *pinfo);

// forks
int				init_forks(t_pinfo *pinfo, size_t size);
void			init_set_forks(t_philo *philo, int i, int amount);

// parse_arg
size_t			*parse_arg(char **av, int size);

// utils
int				ft_atol(const char *str, size_t *dst);
size_t			ft_get_time(void);
void			ft_usleep(size_t ms);

#endif