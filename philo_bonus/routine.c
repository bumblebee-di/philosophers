#include "philo.h"

static void	eat(t_philo *philo)
{
	if (sem_wait(philo->table->fork) == -1)
		exit (1);
	if (sem_wait(philo->table->fork) == -1)
		exit (1);
	print('f', philo, timeinterval(philo->table->start_time));
	philo->last_time_to_eat = timestamp();
	print('e', philo, timeinterval(philo->table->start_time));
	ft_usleep(philo->args->time_to_eat);
	if (sem_post(philo->table->fork) == -1)
		exit (1);
	if (sem_post(philo->table->fork) == -1)
		exit (1);
	if (--philo->n_meals == 0)
		sem_post(philo->table->everyone_is_full);
}

void	*time_line(void *arg)
{
	t_philo	*philo;
	t_table	*table;
	t_args	*args;

	philo = (t_philo *)arg;
	table = philo->table;
	args = philo->args;
	while (1)
	{
		if (timeinterval(philo->last_time_to_eat) > args->time_to_die)
		{
			print('d', philo, timeinterval(table->start_time));
			if (sem_post(philo->table->end_dinner) == -1)
				exit (1);
			exit (0);
		}
		ft_usleep(500);
	}
	return ((void *)0);
}

void	*routine(t_philo	*philo)
{
	pthread_t	th;

	philo->last_time_to_eat = timestamp();
	if (pthread_create(&th, NULL, &time_line, philo) != 0)
		exit (1);
	pthread_detach(th);
	while (1)
	{
		eat(philo);
		print('s', philo, timeinterval(philo->table->start_time));
		ft_usleep(philo->args->time_to_sleep);
		print('t', philo, timeinterval(philo->table->start_time));
	}
}

void	*end_dinner(void *arg)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (t_philo *)arg;
	while (i < philo->args->n_philo)
	{
		if (sem_wait(philo->table->everyone_is_full) == -1)
			exit (1);
		i++;
	}
	if (sem_wait(philo->table->print) == -1)
		exit (1);
	printf("\033[92mAll philosophers ate at least %d times\x1B[0m\n", \
		philo->args->n_to_eat);
	if (sem_post(philo->table->end_dinner) == -1)
		exit (1);
	return ((void *)0);
}
