#include "philo.h"

static int	validate_args(char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (argv[i] && i < 6)
	{
		j = 0;
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) == 0 || argv[i][0] == '0')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static void	args_atoi(t_args *args, char **argv)
{
	args->n_philo = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]) * 1000;
	args->time_to_sleep = ft_atoi(argv[4]) * 1000;
	args->n_to_eat = 0;
}

int	init_args(t_args *args, char **argv, int argc)
{
	if (validate_args(argv) == 0)
		return (0);
	args_atoi(args, argv);
	if (argc == 6)
		args->n_to_eat = ft_atoi(argv[5]);
	return (1);
}

void	init_table(t_args *args, t_table *table)
{
	table->pid = (pid_t *)malloc(sizeof(pid_t) * args->n_philo);
	table->no_dead_body_report = 1;
	table->start_time = -1;
}

void	init_philo(t_args *args, t_table *table, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < args->n_philo)
	{
		philo[i].i = i + 1;
		philo[i].table = table;
		philo[i].args = args;
		philo[i].last_time_to_eat = 0;
		philo[i].n_meals = args->n_to_eat;
		i++;
	}
}
