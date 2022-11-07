/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibalbako <ibalbako@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:41:56 by ibalbako          #+#    #+#             */
/*   Updated: 2022/11/07 11:41:58 by ibalbako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo)
	{
		pthread_mutex_lock(&(data->mut_t));
		if (get_time() - data->philo[i].last_meal_time \
		> (long long)data->time_to_die)
		{
			pthread_mutex_unlock(&(data->mut_t));
			pthread_mutex_lock(&(data->mut_print));
			printf("%llu %d died\n", \
			get_time() - data->start, data->philo->nbr);
			return (1);
		}
		pthread_mutex_unlock(&(data->mut_t));
		i++;
	}
	return (0);
}

static int	check_full(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < data->number_of_philo)
	{
		pthread_mutex_lock(&(data->mut_e));
		if (data->philo[i].eat_count >= data->nb_of_t_each_ph_must_e)
			j++;
		pthread_mutex_unlock(&(data->mut_e));
		i++;
	}
	if (data->number_of_philo == j)
	{
		pthread_mutex_lock(&(data->mut_print));
		printf("all philoophers have eat at least %d times", data->nb_of_t_each_ph_must_e);
		return (1);
	}
	return (0);
}

int	check_end(t_data *data)
{
	while (1)
	{
		if (check_death(data) == 1)
			return (1);
		if (data->nb_of_t_each_ph_must_e != -1)
		{
			if (check_full(data) == 1)
				return (1);
		}
		usleep(300);
	}
	return (0);
}
