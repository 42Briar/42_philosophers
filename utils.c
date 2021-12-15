#include "philo.h"

long	ft_atoi(const char *str)
{
	int		i;
	int		count;
	long	returnal;

	i = 0;
	count = 0;
	returnal = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || \
	str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			count = -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		returnal = returnal * 10 + (str[i] - 48);
		i++;
	}
	if (count == -1)
		returnal = -returnal;
	return (returnal);
}

long long	gettime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	printstatus(char *status, t_philos *philo)
{
	pthread_mutex_lock(&(philo->rules->write));
	if (!philo->rules->death)
	{
		printf("%lld | Philosopher: %d %s\n", \
		(gettime() - philo->rules->start), philo->id, status);
	}
	pthread_mutex_unlock(&(philo->rules->write));
	return ;
}

void	sleeping(long long time)
{
	long long	i;

	i = gettime();
	usleep((time / 2 * 1000));
	while (1)
	{
		if (gettime() - i >= time)
			break ;
		usleep(50);
	}
	return ;
}