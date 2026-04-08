#include "philo.h"

void eat(t_philo *philo)
{
    if (philo->data->num_philos == 1)
    {
        pthread_mutex_lock(philo->left_fork);
        print_action(philo, "has taken a fork");
        smart_sleep(philo->data->time_to_die);
        pthread_mutex_unlock(philo->left_fork);
        return;
    }
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->right_fork);
        print_action(philo, "has taken a fork");
        pthread_mutex_lock(philo->left_fork);
        print_action(philo, "has taken a fork");
    }
    else
    {
        pthread_mutex_lock(philo->left_fork);
        print_action(philo, "has taken a fork");
        pthread_mutex_lock(philo->right_fork);
        print_action(philo, "has taken a fork");
    }
    pthread_mutex_lock(&philo->data->meal_lock);
    philo->last_meal = get_time();
    philo->meals_eaten++;
    pthread_mutex_unlock(&philo->data->meal_lock);
    print_action(philo, "is eating");
    smart_sleep(philo->data->time_to_eat);
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}
