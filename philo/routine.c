#include "philo.h"

static void	eat(t_philo *philo)
{
	int		first_picked;
	int		last_picked;

	first_picked = philo->i - 1;
	last_picked = philo->i % philo->args->n_philo;
	pthread_mutex_lock(&(philo->table->fork[first_picked]));
	pthread_mutex_lock(&(philo->table->fork[last_picked]));
	print('f', philo, timeinterval(philo->table->start_time));
	philo->last_time_to_eat = timestamp();
	print('e', philo, timeinterval(philo->table->start_time));
	ft_usleep(philo->args->time_to_eat);
	pthread_mutex_unlock(&(philo->table->fork[first_picked]));
	pthread_mutex_unlock(&(philo->table->fork[last_picked]));
	if (--philo->n_meals == 0)
		philo->table->everyone_is_full++;
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->i % 2 == 0)
		ft_usleep(philo->args->time_to_eat * 0.5);
	philo->last_time_to_eat = timestamp();
	while (1)
	{
		eat(philo);
		print('s', philo, timeinterval(philo->table->start_time));
		ft_usleep(philo->args->time_to_sleep);
		print('t', philo, timeinterval(philo->table->start_time));
	}
	return ((void *)0);
}

static void	*end_dinner(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print);
	printf("\033[92mAll philosophers ate at least %d times\x1B[0m\n", \
		philo->args->n_to_eat);
	return ((void *)0);
}

void	*time_line(void *arg)
{
	t_philo	*philo;
	t_table	*table;
	t_args	*args;
	int		i;

	philo = (t_philo *)arg;
	table = philo->table;
	args = philo->args;
	while (1)
	{
		i = 0;
		if (table->everyone_is_full == args->n_philo)
			return (end_dinner(philo));
		while (i < args->n_philo)
		{
			if (timeinterval(philo[i].last_time_to_eat) > args->time_to_die)
			{
				print('d', &philo[i], timeinterval(table->start_time));
				return ((void *)0);
			}
			i++;
		}
		ft_usleep(500);
	}
	return ((void *)0);
}
