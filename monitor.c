/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/16 15:33:36 by pvan-dij      #+#    #+#                 */
/*   Updated: 2021/12/16 18:34:16 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	eatcheck(t_rules *rules)
{
	int	i;

	i = 0;
	while (rules->num_eat != -1 && i < rules->philonum && \
		rules->philosophers[i].times_ate >= rules->num_eat)
		i++;
	if (i == rules->philonum)
	{
		rules->state = END;
		return (true);
	}
	return (false);
}

void	deathmonitor(t_rules	*rules)
{
	int		i;

	while (rules->state == RUN)
	{
		i = 0;
		while (i < rules->philonum)
		{
			pthread_mutex_lock(&(rules->philosophers[i].eat));
			if ((gettime() - (rules->philosophers[i].last_meal)) > \
				rules->time_to_die)
			{	
				rules->state = END;
				pthread_mutex_unlock(&(rules->philosophers[i].eat));
				printf("%lld | Philosopher: %d %s\n", \
					(gettime() - rules->start), i + 1, "has died");
				break ;
			}
			pthread_mutex_unlock(&(rules->philosophers[i].eat));
			i++;
		}
		if (eatcheck(rules))
			return ;
	}
	return ;
}

bool	check(t_rules *rules, t_philos *philo)
{
	pthread_mutex_lock(&(philo->eat));
	if ((gettime() - (philo->last_meal)) > \
		rules->time_to_die)
	{	
		rules->state = END;
		pthread_mutex_unlock(&(philo->eat));
		printf("%lld | Philosopher: %d %s\n", \
			(gettime() - rules->start), philo->id, "has died");
		return (true);
	}
	pthread_mutex_unlock(&(philo->eat));
	return (false);
}
