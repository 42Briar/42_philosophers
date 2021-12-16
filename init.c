/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/15 16:26:06 by pvan-dij      #+#    #+#                 */
/*   Updated: 2021/12/16 21:32:23 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philos(t_rules *rules)
{
	int	i;

	i = 0;
	rules->philosophers = (t_philos *)malloc(\
	sizeof(t_philos) * rules->philonum);
	if (!rules->philosophers)
		return (failure(rules));
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
		if (pthread_mutex_init(&(rules->philosophers[i].eat), NULL))
			return (failure(rules));
		i++;
	}
	return (0);
}

int	init(char **argv, int argc, t_rules *rules)
{
	int	i;

	rules->philonum = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	rules->state = RUN;
	if (argc == 6)
		rules->num_eat = ft_atoi(argv[5]);
	else
		rules->num_eat = -1;
	rules->forks = (pthread_mutex_t *)malloc(\
	sizeof(pthread_mutex_t) * rules->philonum);
	if (!rules->forks)
		return (failure(rules));
	i = -1;
	while (++i < rules->philonum)
		if (pthread_mutex_init(&(rules->forks[i]), NULL))
			return (failure(rules));
	if (pthread_mutex_init(&(rules->write), NULL))
		return (failure(rules));
	return (init_philos(rules));
}

bool	digitcheck(char *s)
{
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (false);
		s++;
	}
	return (true);
}

bool	checkarg(int argc, char **argv)
{
	if (!digitcheck(argv[1]) || ft_atoi(argv[1]) > 200 || ft_atoi(argv[1]) <= 0)
		return (false);
	if (!digitcheck(argv[2]) || ft_atoi(argv[2]) < 60)
		return (false);
	if (!digitcheck(argv[3]) || ft_atoi(argv[3]) < 60)
		return (false);
	if (!digitcheck(argv[4]) || ft_atoi(argv[4]) < 60)
		return (false);
	if (argc == 6)
		if (!digitcheck(argv[5]) || ft_atoi(argv[5]) <= 0)
			return (false);
	return (true);
}
