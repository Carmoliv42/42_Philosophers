#include "philo.h"

void eat(t_philo *philo)
{
    pthread_mutex_t *first;
    pthread_mutex_t *second;

    // 🔴 Se só há 1 filósofo
    if (philo->data->num_philos == 1)
    {
        pthread_mutex_lock(philo->left_fork);
        print_action(philo, "has taken a fork");
        smart_sleep(philo, philo->data->time_to_die);
        pthread_mutex_unlock(philo->left_fork);
        return;
    }
    pthread_mutex_lock(&philo->data->death_lock);
    if (philo->data->simulation_end)
    {
        pthread_mutex_unlock(&philo->data->death_lock);
        return;
    }
    pthread_mutex_unlock(&philo->data->death_lock);

    // 🔥 ORDEM SEGURA (evita deadlock)
    if (philo->left_fork < philo->right_fork)
    {
        first = philo->left_fork;
        second = philo->right_fork;
    }
    else
    {
        first = philo->right_fork;
        second = philo->left_fork;
    }
    pthread_mutex_lock(first);
    print_action(philo, "has taken a fork");
    pthread_mutex_lock(second);
    print_action(philo, "has taken a fork");
    // 🔒 Atualiza estado da refeição
    pthread_mutex_lock(&philo->data->meal_lock);
    philo->last_meal = get_time();
    philo->meals_eaten++;
    pthread_mutex_unlock(&philo->data->meal_lock);
    print_action(philo, "is eating");
    smart_sleep(philo, philo->data->time_to_eat);
    pthread_mutex_unlock(second);
    pthread_mutex_unlock(first);
}

