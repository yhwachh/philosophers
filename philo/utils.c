/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibalbako <ibalbako@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:42:56 by ibalbako          #+#    #+#             */
/*   Updated: 2022/11/10 11:27:47 by ibalbako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping(long long time)
{
	long long	real_time;

	real_time = get_time();
	usleep(time * 920);
	while (time > (get_time() - real_time))
		usleep(90);
}

int	print(t_philo *ph, char *str)
{
	if (ph->data->dead == 1)
		return (0);
	pthread_mutex_lock(&(ph->data->mut_print));
	printf("%llu %d %s\n", get_time() - ph->data->start, ph->nbr, str);
	pthread_mutex_unlock(&(ph->data->mut_print));
	return (0);
}

long long int	get_time(void)
{
	struct timeval	t;
	long long int	ms;

	gettimeofday(&t, 0);
	ms = t.tv_sec * 1000 + t.tv_usec / 1000;
	return (ms);
}

void	free_all_and_destroy(t_data *data)
{
	int	i;

	i = 0;
	free(data->philo);
	data->philo = NULL;
	while (i < data->number_of_philo)
	{
		pthread_mutex_unlock(&(data->forks[i]));
		pthread_mutex_destroy(&(data->forks[i]));
		i++;
	}
	free(data->forks);
	pthread_mutex_destroy(&(data->mut_print));
	free(data->threads);
	free(data);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	egal;

	sign = 1;
	egal = 0;
	i = 0;
	while (str[i] && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
	{
		i++;
	}
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		egal = egal * 10 + (str[i] - '0');
		i++;
	}
	return (egal * sign);
}
