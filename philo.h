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

typedef struct s_rules {
	int				philonum;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_eat;
	long long		start;
	bool			death;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t	mutex_death;
	t_philos		*philosophers;
}	t_rules;

struct s_philo {
	int			id;
	int			r_fork;
	int			l_fork;
	int			times_ate;
	long long	last_meal;
	pthread_t	thread;
	t_rules		*rules;
};

long		ft_atoi(const char *str);
void		init(char **argv, int argc, t_rules *rules);
long long	gettime(void);
void		printstatus(char *status, t_philos *philo);
bool		checkdeath(t_rules *rules);
void		sleeping(long long time);
bool		checkarg(int argc, char **argv);
bool		is_dead(t_philos *philo);

#endif