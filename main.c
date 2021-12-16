/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/15 16:26:03 by pvan-dij      #+#    #+#                 */
/*   Updated: 2021/12/16 18:50:07 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philos *philo)
{
	pthread_mutex_lock(&(philo->rules->forks[philo->l_fork]));
	printstatus("has taken a fork", philo);
	if (philo->rules->philonum == 1)
	{
		pthread_mutex_unlock(&(philo->rules->forks[philo->l_fork]));
		return ;
	}
	pthread_mutex_lock(&(philo->rules->forks[philo->r_fork]));
	printstatus("has taken a fork", philo);
	printstatus("is eating", philo);
	pthread_mutex_lock(&(philo->eat));
	philo->last_meal = gettime();
	philo->times_ate++;
	pthread_mutex_unlock(&(philo->eat));
	sleeping(philo->rules->time_to_eat);
	pthread_mutex_unlock(&(philo->rules->forks[philo->l_fork]));
	pthread_mutex_unlock(&(philo->rules->forks[philo->r_fork]));
}

void	*philo_thread(void *p)
{
	t_philos	*philo;

	philo = (t_philos *)p;
	if (philo->id % 2 == 0)
		sleeping(philo->rules->time_to_eat / 2);
	while (philo->rules->state == RUN)
	{
		eat(philo);
		if (philo->rules->philonum == 1)
			return (NULL);
		printstatus("is sleeping", philo);
		sleeping(philo->rules->time_to_sleep);
		printstatus("is thinking", philo);
	}
	return (NULL);
}

void	run_philos(t_rules *rules)
{
	int			i;

	i = 0;
	rules->start = gettime();
	while (i < rules->philonum)
	{
		rules->philosophers[i].last_meal = rules->start;
		pthread_create(&(rules->philosophers[i].thread), \
		NULL, philo_thread, &(rules->philosophers[i]));
		i++;
	}
	deathmonitor(rules);
	i = -1;
	while (++i < rules->philonum)
		pthread_join((rules->philosophers[i].thread), NULL);
	i = 0;
	while (i++ < rules->philonum)
	{
		pthread_mutex_destroy(&(rules->forks[i]));
		pthread_mutex_destroy(&(rules->philosophers[i].eat));
	}	
	pthread_mutex_destroy(&(rules->write));
}

int	main(int argc, char *argv[])
{
	t_rules	*rules;

	rules = (t_rules *)malloc(sizeof(t_rules));
	if (argc < 5 || argc > 6)
		return (0);
	if (!checkarg(argc, argv))
		return (0);
	init(argv, argc, rules);
	run_philos(rules);
	return (1);
}
