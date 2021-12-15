/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/15 16:26:03 by pvan-dij      #+#    #+#                 */
/*   Updated: 2021/12/15 17:07:59 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	deathcheck(t_rules *rules)
{
	int	i;

	while (true)
	{
		i = 0;
		while (i < rules->philonum)
		{
			pthread_mutex_lock(&(rules->mutex_death));
			if ((gettime() - (rules->philosophers[i].last_meal)) > \
			rules->time_to_die)
			{	
				printstatus("has died", &(rules->philosophers[i]), 1);
				rules->death = true;
				pthread_mutex_unlock(&(rules->mutex_death));
				return ;
			}
			pthread_mutex_unlock(&(rules->mutex_death));
			i++;
		}
		i = 0;
		while (rules->num_eat != -1 && i < rules->philonum && rules->philosophers[i].times_ate >= rules->num_eat)
			i++;
		if (i == rules->philonum)
		{
			pthread_mutex_lock(&(rules->mutex_death));
			rules->death = true;
			pthread_mutex_unlock(&(rules->mutex_death));
			break ;
		}
		pthread_mutex_lock(&(rules->mutex_death));
		if (rules->death == true)
		{
			pthread_mutex_unlock(&(rules->mutex_death));
			break ;
		}
		pthread_mutex_unlock(&(rules->mutex_death));
	}
}

bool	is_dead(t_philos *philo)
{
	pthread_mutex_lock(&(philo->rules->mutex_death));
	if ((gettime() - philo->last_meal) > philo->rules->time_to_die || \
	philo->rules->death)
	{	
		if (!philo->rules->death)
		{
			printstatus("has died", philo, 1);
			philo->rules->death = true;
		}
		pthread_mutex_unlock(&(philo->rules->mutex_death));
		return (true);
	}
	pthread_mutex_unlock(&(philo->rules->mutex_death));
	return (false);
}

void	*philo_thread(void *philos)
{
	t_philos	*philo;

	philo = (t_philos *)philos;
	if (philo->id % 2 == 0)
		usleep(philo->rules->time_to_eat * 500);
	while (true)
	{
		pthread_mutex_lock(&(philo->rules->forks[philo->l_fork]));
		printstatus("has taken a fork", philos, 0);
		if (philo->rules->philonum == 1)
		{
			pthread_mutex_unlock(&(philo->rules->forks[philo->l_fork]));
			return (NULL);
		}
		pthread_mutex_lock(&(philo->rules->forks[philo->r_fork]));
		if (is_dead(philo))
		{
			pthread_mutex_unlock(&(philo->rules->forks[philo->l_fork]));
			pthread_mutex_unlock(&(philo->rules->forks[philo->r_fork]));
			break ;
		}
		printstatus("has taken a fork", philos, 0);
		printstatus("is eating", philos, 0);
		philo->last_meal = gettime();
		sleeping(philo->rules->time_to_eat);
		philo->times_ate++;
		pthread_mutex_unlock(&(philo->rules->forks[philo->l_fork]));
		pthread_mutex_unlock(&(philo->rules->forks[philo->r_fork]));
		printstatus("is sleeping", philos, 0);
		sleeping(philo->rules->time_to_sleep);
		printstatus("is thinking", philos, 0);
	}
	return (NULL);
}

void	run_philos(t_rules *rules)
{
	int	i;

	i = 0;
	rules->start = gettime();
	while (i < rules->philonum)
	{
		rules->philosophers[i].last_meal = rules->start;
		pthread_create(&(rules->philosophers[i].thread), \
		NULL, philo_thread, &(rules->philosophers[i]));
		i++;
	}
	i = 0;
	deathcheck(rules);
	while (i < rules->philonum)
	{
		pthread_join((rules->philosophers[i].thread), NULL);
		i++;
	}
	i = 0;
	while (i++ < rules->philonum)
		pthread_mutex_destroy(&(rules->forks[i]));
	pthread_mutex_destroy(&(rules->write));
	pthread_mutex_destroy(&(rules->mutex_death));
}

int	main(int argc, char *argv[])
{
	t_rules	rules;

	if (argc < 5 || argc > 6)
		return (0);
	if (!checkarg(argc, argv))
		return (0);
	init(argv, argc, &rules);
	run_philos(&rules);
	return (1);
}

/*
consider removing death monitor and replacing it with checker function called from inside philo thread
and need to remove the many data races
*/

//fsanitize=thread
//https://github.com/MichelleJiam/LazyPhilosophersTester
