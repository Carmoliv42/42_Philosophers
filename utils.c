#include "philo.h"

long	get_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	
}

void	smart_sleep(long time)
{
	long start;

	start = get_time();
	while(get_time() - start < time)
		usleep(500);
}

void	print_action(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->print_lock);
	if(!philo->data->simulation_end)
		printf("%ld %d %s\n", get_time() - philo->data->start_time,
			philo->id, str);
	pthread_mutex_unlock(&philo->data->print_lock);
}