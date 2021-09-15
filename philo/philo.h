#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_table {
	int				everyone_is_full;
	int				no_dead_body_report;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	int				philo_start;
	long			start_time;
}	t_table;

typedef struct s_args {
	int		n_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		n_to_eat;
}	t_args;

typedef struct s_philo {
	int			i;
	int			n_meals;
	t_table		*table;
	t_args		*args;
	long		last_time_to_eat;
}	t_philo;

/*--- init.c ---*/

int			init_args(t_args *args, char **argv, int argc);
void		init_philo(t_args *args, t_table *table, t_philo *philo);
void		init_table(t_args *args, t_table *table);

/*--- routine.c ---*/

void		*routine(void *arg);
long		timestamp(void);
long		timeinterval(long start_time);
void		*time_line(void *arg);

/*--- utils.c ---*/

void		print(char type, t_philo *philo, long time_stamp);
void		ft_usleep(long time);

/*--- libft_utils.c ---*/

int			ft_atoi(const char *str);
int			ft_isdigit(int c);

#endif
