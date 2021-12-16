/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/16 21:03:18 by pvan-dij      #+#    #+#                 */
/*   Updated: 2021/12/16 21:29:27 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	cleanup(t_rules *rules)
{
	int	i;

	i = 0;
	while (i++ < rules->philonum)
	{
		pthread_mutex_destroy(&(rules->forks[i]));
		pthread_mutex_destroy(&(rules->philosophers[i].eat));
	}	
	pthread_mutex_destroy(&(rules->write));
	free(rules);
	return (1);
}

int	failure(t_rules *rules)
{
	write(1, "Critical error\n", 15);
	free(rules);
	return (1);
}

int	killthreads(t_rules *rules, int i)
{
	while (--i >= 0)
		pthread_detach((rules->philosophers[i].thread));
	return (cleanup(rules));
}
