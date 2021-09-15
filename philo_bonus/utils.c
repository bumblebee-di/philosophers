#include "philo.h"

long	timestamp(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

long	timeinterval(long start_time)
{
	long	current_time;

	if (start_time == 0)
		return (0);
	current_time = timestamp();
	return (current_time - start_time);
}

void	print(char type, t_philo *philo, long time)
{
	if (sem_wait(philo->table->print) == -1)
		exit (1);
	if (philo->table->no_dead_body_report)
	{
		if (type == 'd')
		{
			philo->table->no_dead_body_report = 0;
			printf("%ld ms %d \x1B[31mdied\x1B[0m\n", time, philo->i);
			return ;
		}
		if (type == 'f')
		{
			printf("%ld ms %d has taken a first fork\n", time, philo->i);
			printf("%ld ms %d has taken a second fork\n", time, philo->i);
		}
		else if (type == 'e')
			printf("%ld ms %d is eating\n", time, philo->i);
		else if (type == 's')
			printf("%ld ms %d is sleeping\n", time, philo->i);
		else if (type == 't')
			printf("%ld ms %d is thinking\n", time, philo->i);
	}
	if (sem_post(philo->table->print) == -1)
		exit (1);
}

void	ft_usleep(long time)
{
	long	sleep_time;

	sleep_time = timestamp() * 1000 + time;
	while (1)
	{
		usleep(50);
		if (sleep_time < timestamp() * 1000)
			break ;
	}
}
