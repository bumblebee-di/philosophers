#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <signal.h>
# include <semaphore.h>

# define SEM_PERMS 0644
# define SEM_FORK "/forks_for_philosophers"
# define SEM_PRINT "/block_for_printing"
# define SEM_STOP "/philos_ate_at_least_n_times"
# define SEM_END "/philos_bonus_end_dinner"

typedef struct s_table {
	long			start_time;
	int				no_dead_body_report;
	sem_t			*everyone_is_full;
	sem_t			*fork;
	sem_t			*print;
	sem_t			*end_dinner;
	pid_t			*pid;
}	t_table;

typedef struct s_args {
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		n_to_eat;
	int		n_philo;
}	t_args;

typedef struct s_philo {
	t_table		*table;
	t_args		*args;
	int			i;
	int			n_meals;
	long		last_time_to_eat;
}	t_philo;

/*--- init.c ---*/

int			init_args(t_args *args, char **argv, int argc);
void		init_philo(t_args *args, t_table *table, t_philo *philo);
void		init_table(t_args *args, t_table *table);

/*--- routine.c ---*/

void		*routine(t_philo	*philo);
long		timestamp(void);
long		timeinterval(long start_time);
void		*time_line(void *arg);
void		*end_dinner(void *arg);

/*--- utils.c ---*/

void		print(char type, t_philo *philo, long time_stamp);
void		ft_usleep(long time);

/*--- libft_utils.c ---*/

int			ft_atoi(const char *str);
int			ft_isdigit(int c);

#endif