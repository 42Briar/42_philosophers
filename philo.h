/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/15 16:26:13 by pvan-dij      #+#    #+#                 */
/*   Updated: 2021/12/16 21:27:24 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>
# include <stdbool.h>

typedef struct s_philo	t_philos;

typedef enum e_runtime {
	RUN,
	END
}	t_run;

typedef struct s_rules {
	int				philonum;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_eat;
	long long		start;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	t_philos		*philosophers;
	t_run			state;
}	t_rules;

struct s_philo {
	int				id;
	int				r_fork;
	int				l_fork;
	int				times_ate;
	long long		last_meal;
	pthread_t		thread;
	pthread_mutex_t	eat;
	t_rules			*rules;
};

long		ft_atoi(const char *str);
int			init(char **argv, int argc, t_rules *rules);
long long	gettime(void);
void		printstatus(char *status, t_philos *philo);
void		sleeping(long long time);
bool		checkarg(int argc, char **argv);
void		deathmonitor(t_rules *rules);
int			cleanup(t_rules *rules);
int			failure(t_rules *rules);
int			ft_isdigit(int c);
int			killthreads(t_rules *rules, int i);

#endif