/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibalbako <ibalbako@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:26:53 by ibalbako          #+#    #+#             */
/*   Updated: 2022/11/10 11:26:57 by ibalbako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat_philo(t_philo *ph)
{
	if (ph->data->dead == 1)
		return ;
	pthread_mutex_lock(&(ph->data->forks[ph->r_fork - 1]));
	print(ph, "has taken a fork");
	pthread_mutex_lock(&(ph->data->forks[ph->l_fork - 1]));
	print(ph, "has taken a fork");
	ph->last_meal_time = get_time();
	print(ph, "is eating");
	if (ph->data->dead == 1)
		return ;
	sleeping(ph->data->time_to_eat);
	pthread_mutex_unlock(&(ph->data->forks[ph->l_fork - 1]));
	pthread_mutex_unlock(&(ph->data->forks[ph->r_fork - 1]));
	ph->eat_count++;
	return ;
}

void	*ph_rutin(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	if (ph->nbr % 2 == 0)
		usleep(600);
	while (1)
	{
		if (ph->data->dead == 1)
			break ;
		eat_philo(ph);
		print(ph, "is sleeping");
		sleeping(ph->data->time_to_sleep);
		print(ph, "is thinking");
		usleep(200);
	}
	return (0);
}

int	treads(t_data *d)
{
	int	i;

	i = 0;
	d->forks = malloc(sizeof(pthread_mutex_t) * d->number_of_philo);
	while (i < d->number_of_philo)
		pthread_mutex_init(&(d->forks[i++]), NULL);
	pthread_mutex_init(&(d->mut_print), NULL);
	d->threads = malloc(sizeof(pthread_t) * d->number_of_philo);
	if (d->forks == NULL || d->threads == NULL)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	i = -1;
	while (++i < d->number_of_philo)
	{
		if (pthread_create(&(d->threads[i]), NULL, ph_rutin, &(d->philo[i])))
			return (1);
	}
	i = 0;
	while (i < d->number_of_philo)
		pthread_detach(d->threads[i++]);
	return (0);
}
