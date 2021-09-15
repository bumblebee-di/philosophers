#include "philo.h"

static int	come_to_kitchen(t_philo *philo, pthread_t *th)
{
	t_table	*table;
	int		i;

	i = 0;
	table = philo[0].table;
	philo->table->start_time = timestamp();
	while (i < philo[0].args->n_philo)
	{
		if (pthread_create(&th[i], NULL, &routine, &philo[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_create(&th[i], NULL, &time_line, philo) != 0)
		return (1);
	return (0);
}

static int	leave_kitchen(t_philo *philo, pthread_t *th)
{
	int		i;
	void	*ret;

	i = 0;
	ret = NULL;
	while (i < philo[0].args->n_philo)
	{
		if (pthread_detach(th[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_join(th[i], ret) != 0)
		return (1);
	i = 0;
	while (i < philo[0].args->n_philo)
	{
		pthread_mutex_destroy(&(philo[0].table->fork[i]));
		i++;
	}
	pthread_mutex_destroy(&(philo[0].table->print));
	return (0);
}

static void	dining_philosophers(t_philo *philo)
{
	pthread_t	*th;
	t_table		*table;
	int			n_philo;
	int			i;

	i = 0;
	n_philo = philo[0].args->n_philo;
	table = philo[0].table;
	th = (pthread_t *)malloc(sizeof(pthread_t) * (n_philo + 1));
	pthread_mutex_init(&(table->print), NULL);
	while (i < n_philo)
	{
		pthread_mutex_init(&(table->fork[i]), NULL);
		i++;
	}
	if (come_to_kitchen(philo, th) == 0)
		leave_kitchen(philo, th);
	free(table->fork);
	free(th);
	free(philo);
}

int	main(int argc, char **argv)
{
	t_args	args;
	t_table	table;
	t_philo	*philo;

	if (argc > 6 || argc < 5)
		return (1);
	if (init_args(&args, argv, argc) == 1)
	{
		init_table(&args, &table);
		philo = malloc(sizeof(t_philo) * args.n_philo);
		init_philo(&args, &table, philo);
		dining_philosophers(philo);
		return (0);
	}
	return (1);
}
