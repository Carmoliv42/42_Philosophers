#include "philo.h"
 
int init_data(t_data *data, char **av)
{
    data->num_philos = atoi(av[1]);
    data->time_to_die = atol(av[2]);
    data->time_to_eat = atol(av[3]);
    data->time_to_sleep = atol(av[4]);
    data->must_eat = (av[5]) ? atoi(av[5]) : -1;
    data->simulation_end = 0;
 
    data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
    data->philos = malloc(sizeof(t_philo) * data->num_philos);
 
    if (!data->forks || !data->philos)
        return (1);
 
    pthread_mutex_init(&data->print_lock, NULL);
    pthread_mutex_init(&data->death_lock, NULL);
    pthread_mutex_init(&data->meal_lock, NULL);
 
    for (int i = 0; i < data->num_philos; i++)
        pthread_mutex_init(&data->forks[i], NULL);
 
    data->start_time = get_time();
    return (0);
}
 
int init_philos(t_data *data)
{
    int i;
 
    i = 0;
    while (i < data->num_philos)
    {
        data->philos[i].id = i + 1;
        data->philos[i].meals_eaten = 0;
        data->philos[i].last_meal = data->start_time;
        data->philos[i].left_fork = &data->forks[i];
        data->philos[i].right_fork =
            &data->forks[(i + 1) % data->num_philos];
        data->philos[i].data = data;
        i++;
    }
    return (0);
}