#include "philo.h"

int main(int ac, char **av)
{
    t_data  data;
    pthread_t monitor;
    int i;

    if(ac < 5 || ac > 6)
        return (printf("Error: Wrong arguments\n"),1);
    if(init_data(&data, av) || init_philos(&data))
        return(printf("Error: init failed\n"),1);
    i = 0;
    while(i < data.num_philos)
    {
        pthread_create(&data.philos[i].thread, NULL, philo_routine, &data.philos[i]);
        i++;
    }
    pthread_create(&monitor, NULL, monitor_routine, &data);
    i = 0;
    while(i < data.num_philos)
    {
        pthread_join(data.philos[i].thread, NULL);
        i++;
    }
    pthread_join(monitor, NULL);
    free(data.philos);
    free(data.forks);
    return (0);
}
