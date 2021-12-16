/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/16 15:33:36 by pvan-dij      #+#    #+#                 */
/*   Updated: 2021/12/16 20:49:11 by pvan-dij      ########   odam.nl         */
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

	while (true)
	{
		i = 0;
		while (i < rules->philonum)
		{
			pthread_mutex_lock(&(rules->philosophers[i].eat));
			if ((gettime() - (rules->philosophers[i].last_meal)) > \
				rules->time_to_die)
			{	
				printstatus("has died", &(rules->philosophers[i]));
				pthread_mutex_lock(&(rules->write));
				rules->state = END;
				pthread_mutex_unlock(&(rules->write));
				pthread_mutex_unlock(&(rules->philosophers[i].eat));
				return ;
			}
			pthread_mutex_unlock(&(rules->philosophers[i].eat));
			i++;
		}
		if (eatcheck(rules))
			return ;
	}
	return ;
}
