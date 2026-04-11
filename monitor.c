#include "philo.h"

static int check_philo(t_data *data, int i, int *full_count)
{
	long last;

	pthread_mutex_lock(&data->meal_lock);
	last = data->philos[i].last_meal;
	if (data->must_eat != -1
		&& data->philos[i].meals_eaten >= data->must_eat)
		(*full_count)++;
	pthread_mutex_unlock(&data->meal_lock);

	if (get_time() - last > data->time_to_die)
	{
		pthread_mutex_lock(&data->death_lock);
		if (!data->simulation_end)
		{
			data->simulation_end = 1;
			pthread_mutex_lock(&data->print_lock);
			printf("%ld %d died\n",
				get_time() - data->start_time,
				data->philos[i].id);
			pthread_mutex_unlock(&data->print_lock);
		}
		pthread_mutex_unlock(&data->death_lock);
		return (1);
	}
	return (0);
}

static int monitor_philos(t_data *data)
{
	int i;
	int full_count;

	i = 0;
	full_count = 0;
	while (i < data->num_philos)
	{
		if (check_philo(data, i, &full_count))
			return (1);
		i++;
	}

	if (data->must_eat != -1 && full_count == data->num_philos)
	{
		pthread_mutex_lock(&data->death_lock);
		data->simulation_end = 1;
		pthread_mutex_unlock(&data->death_lock);
		return (1);
	}
	return (0);
}

void *monitor_routine(void *arg)
{
	t_data *data;

	data = (t_data *)arg;

	while (1)
	{
		pthread_mutex_lock(&data->death_lock);
		if (data->simulation_end)
		{
			pthread_mutex_unlock(&data->death_lock);
			break;
		}
		pthread_mutex_unlock(&data->death_lock);

		if (monitor_philos(data))
			return (NULL);

		usleep(1000);
	}
	return (NULL);
}
