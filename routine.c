#include "philo.h"

void think(t_philo *philo)
{
    print_action(philo, "is thinking");
    usleep(500);
}

void	sleep_philo(t_philo *philo)
{
	print_action(philo, "is sleeping");
	smart_sleep(philo, philo->data->time_to_sleep);
}

void *philo_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	if (philo->id % 2 == 0)
		usleep(500);

	while (1)
	{
		pthread_mutex_lock(&philo->data->death_lock);
		if (philo->data->simulation_end)
		{
			pthread_mutex_unlock(&philo->data->death_lock);
			break;
		}
		pthread_mutex_unlock(&philo->data->death_lock);

		eat(philo);
		sleep_philo(philo);
		think(philo);
	}
	return (NULL);
}
