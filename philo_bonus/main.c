#include "philo.h"

static int	create_child_process(int i, t_table *table)
{
	table->pid[i] = fork();
	if (table->pid[i] < 0)
	{
		write(STDIN_FILENO, "fork error\n", 11);
		return (0);
	}
	else if (table->pid[i] == 0)
		return (1);
	return (0);
}

static void	come_to_kitchen(t_philo *philo)
{
	t_table	*table;
	int		i;

	i = 0;
	table = philo[0].table;
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_STOP);
	sem_unlink(SEM_END);
	table->fork = sem_open(SEM_FORK, O_CREAT, SEM_PERMS, philo->args->n_philo);
	table->print = sem_open(SEM_PRINT, O_CREAT, SEM_PERMS, 1);
	table->everyone_is_full = sem_open(SEM_STOP, O_CREAT, SEM_PERMS, 0);
	table->end_dinner = sem_open(SEM_END, O_CREAT, SEM_PERMS, 0);
	if (table->fork == SEM_FAILED || table->everyone_is_full == SEM_FAILED || \
		table->print == SEM_FAILED || table->end_dinner == SEM_FAILED)
		exit (1);
	philo->table->start_time = timestamp();
	while (i < philo[0].args->n_philo)
	{
		if (create_child_process(i, table) == 1)
			routine(philo + i);
		i++;
	}
	return ;
}

static void	leave_kitchen(t_philo *philo)
{
	pthread_t	th;
	t_table		*table;
	void		*ret;
	int			i;

	i = 0;
	ret = NULL;
	table = philo[0].table;
	if (philo->args->n_to_eat != 0)
	{
		if (pthread_create(&th, NULL, &end_dinner, philo) != 0)
			exit (1);
	}
	if (sem_wait(philo->table->end_dinner) == -1)
		exit (1);
	while (i < philo[0].args->n_philo)
	{
		kill(table->pid[i], SIGTERM);
		i++;
	}
	free(philo->table->pid);
	return ;
}

static void	dining_philosophers(t_philo *philo)
{
	int	i;

	i = 0;
	come_to_kitchen(philo);
	leave_kitchen(philo);
	sem_close(philo->table->fork);
	sem_close(philo->table->print);
	if (sem_post(philo->table->end_dinner) == -1)
		exit (1);
	sem_close(philo->table->end_dinner);
	if (sem_post(philo->table->everyone_is_full) == -1)
		exit (1);
	sem_close(philo->table->everyone_is_full);
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_STOP);
	sem_unlink(SEM_END);
	free(philo);
	return ;
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
