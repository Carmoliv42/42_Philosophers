#include "philo.h"

void    *monitor_routine(void *arg)
{
    t_data *data;
    int i;
    int full_count;

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

        i = 0;
        full_count = 0;
        while (i < data->num_philos)
        {
            // 🔴 CORREÇÃO: usar meal_lock aqui
            pthread_mutex_lock(&data->meal_lock);

            if (get_time() - data->philos[i].last_meal > data->time_to_die)
            {
                pthread_mutex_unlock(&data->meal_lock);

                pthread_mutex_lock(&data->death_lock);
                if (!data->simulation_end)
                {
                    print_action(&data->philos[i], "died");
                    data->simulation_end = 1;
                }
                pthread_mutex_unlock(&data->death_lock);
                return (NULL);
            }

            if (data->must_eat != -1
                && data->philos[i].meals_eaten >= data->must_eat)
                full_count++;

            pthread_mutex_unlock(&data->meal_lock);
            i++;
        }

        if (data->must_eat != -1 && full_count == data->num_philos)
        {
            pthread_mutex_lock(&data->death_lock);
            data->simulation_end = 1;
            pthread_mutex_unlock(&data->death_lock);
            return (NULL);
        }

        usleep(1000);
    }
    return (NULL);
}
