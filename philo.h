#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct s_data t_data;

typedef struct s_philo
{
    int				id;
	int				meals_eaten;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t *right_fork;
	t_data			*data;
} t_philo;

typedef struct s_data
{
	int				num_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				must_eat;

	long			start_time;
	int				simulation_end;

	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	death_lock;

	t_philo			*philos;
} t_data;

/*utils*/
long	get_time(void);
void	smart_sleep(long time);
void	print_action(t_philo *philo, char *str);

/*action*/
void	eat(t_philo *philo);

/*init*/
int	init_data(t_data *data, char **av);
int	init_philos(t_data *data);

/*routine*/
void	*philo_routine(void *arg);

/*monitor*/
void	monitor_routine(void *arg);

#endif