#include "philo.h"

void	init_philos(t_rules *rules)
{
	int	i;

	i = 0;
	rules->philosophers = (t_philos *)malloc(\
	sizeof(t_philos) * rules->philonum);
	while (i < rules->philonum)
	{
		rules->philosophers[i].id = i + 1;
		rules->philosophers[i].last_meal = 0;
		rules->philosophers[i].times_ate = 0;
		rules->philosophers[i].l_fork = i;
		if (i + 1 == rules->philonum)
			rules->philosophers[i].r_fork = 0;
		else
			rules->philosophers[i].r_fork = i + 1;
		rules->philosophers[i].rules = rules;
		i++;
	}
}

void	init(char **argv, int argc, t_rules *rules)
{
	int	i;

	rules->philonum = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	rules->death = false;
	if (argc == 6)
		rules->num_eat = ft_atoi(argv[5]);
	else
		rules->num_eat = -1;
	rules->forks = (pthread_mutex_t *)malloc(\
	sizeof(pthread_mutex_t) * rules->philonum);
	i = -1;
	while (++i < rules->philonum)
		pthread_mutex_init(&(rules->forks[i]), NULL);
	pthread_mutex_init(&(rules->write), NULL);
	pthread_mutex_init(&(rules->mutex_death), NULL);
	init_philos(rules);
}

bool	checkarg(int argc, char **argv)
{
	if (ft_atoi(argv[1]) > 200 || ft_atoi(argv[1]) <= 0)
		return (false);
	if (ft_atoi(argv[2]) < 60)
		return (false);
	if (ft_atoi(argv[3]) < 60)
		return (false);
	if (ft_atoi(argv[4]) < 60)
		return (false);
	if (argc == 6)
		if (ft_atoi(argv[5]) <= 0)
			return (false);
	return (true);
}