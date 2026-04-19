#include "philo.h"
 
void take_forks(t_philo *philo, pthread_mutex_t **first, pthread_mutex_t **second)
{
	if (philo->left_fork < philo->right_fork)
	{
		*first = philo->left_fork;
		*second = philo->right_fork;
	}
	else
	{
		*first = philo->right_fork;
		*second = philo->left_fork;
	}
 
	pthread_mutex_lock(*first);
	print_action(philo, "has taken a fork");
 
	pthread_mutex_lock(*second);
	print_action(philo, "has taken a fork");
}
 
static void	do_eat(t_philo *philo,
	pthread_mutex_t *first, pthread_mutex_t *second)
{
	print_action(philo, "is eating");
 
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_lock);
 
	smart_sleep(philo, philo->data->time_to_eat);
 
	pthread_mutex_unlock(second);
	pthread_mutex_unlock(first);
}
 
void	eat(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;
 
	if (philo->data->num_philos == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		while (1)
		{
			pthread_mutex_lock(&philo->data->death_lock);
			if (philo->data->simulation_end)
			{
				pthread_mutex_unlock(&philo->data->death_lock);
				pthread_mutex_unlock(philo->left_fork);
				return;
			}
			pthread_mutex_unlock(&philo->data->death_lock);
			usleep(100);
		}
	}
 
	pthread_mutex_lock(&philo->data->death_lock);
	if (philo->data->simulation_end)
	{
		pthread_mutex_unlock(&philo->data->death_lock);
		return;
	}
	pthread_mutex_unlock(&philo->data->death_lock);
 
	take_forks(philo, &first, &second);
	do_eat(philo, first, second);
}