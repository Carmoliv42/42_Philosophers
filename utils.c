/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 15:41:56 by carmoliv          #+#    #+#             */
/*   Updated: 2026/06/27 20:00:22 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	smart_sleep(t_philo *philo, long time)
{
	long	start;

	start = get_time();
	while (get_time() - start < time)
	{
		pthread_mutex_lock(&philo->data->death_lock);
		if (philo->data->simulation_end)
		{
			pthread_mutex_unlock(&philo->data->death_lock);
			return ;
		}
		pthread_mutex_unlock(&philo->data->death_lock);
		usleep(100);
	}
}

void	print_action(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->death_lock);
	if (philo->data->simulation_end)
	{
		pthread_mutex_unlock(&philo->data->death_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->data->death_lock);
	pthread_mutex_lock(&philo->data->print_lock);
	printf("%ld %d %s\n",
		get_time() - philo->data->start_time,
		philo->id, str);
	pthread_mutex_unlock(&philo->data->print_lock);
}
