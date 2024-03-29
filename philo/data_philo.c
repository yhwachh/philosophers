/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibalbako <ibalbako@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:41:56 by ibalbako          #+#    #+#             */
/*   Updated: 2022/11/10 11:21:39 by ibalbako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	if_death(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo)
	{
		if (get_time() - data->philo[i].last_meal_time \
		> (long long)data->time_to_die)
		{
			data->dead = 1;
			pthread_mutex_lock(&(data->mut_print));
			printf("%llu %d died\n", \
			get_time() - data->start, data->philo->nbr);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	if_full(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < data->number_of_philo)
	{
		if (data->philo[i].eat_count >= data->nb_of_t_each_ph_must_e)
			j++;
		i++;
	}
	if (data->number_of_philo == j)
	{
		pthread_mutex_lock(&(data->mut_print));
		printf("%d times", data->nb_of_t_each_ph_must_e);
		return (1);
	}
	return (0);
}

int	if_end(t_data *data)
{
	while (1)
	{
		if (data->dead == 1)
			return (0);
		if (if_death(data) == 1)
			return (1);
		if (data->nb_of_t_each_ph_must_e != -1)
		{
			if (if_full(data) == 1)
				return (1);
		}
		usleep(300);
	}
	return (0);
}
