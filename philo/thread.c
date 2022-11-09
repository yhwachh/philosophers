#include "philo.h"

static void	eat_philo(t_philo *ph)
{
	if (ph->info->dead == 1)
		return ;
	pthread_mutex_lock(&(ph->info->forks[ph->r_fork - 1]));
	print(ph, "has taken a fork");
	pthread_mutex_lock(&(ph->info->forks[ph->l_fork - 1]));
	print(ph, "has taken a fork");
	ph->last_meal_time = get_time();
	print(ph, "is eating");
	if (ph->info->dead == 1)
		return ;
	my_usleep(ph->info->time_to_eat);
	pthread_mutex_unlock(&(ph->info->forks[ph->l_fork - 1]));
	pthread_mutex_unlock(&(ph->info->forks[ph->r_fork - 1]));
	ph->eat_count++;
	return ;
}

void	*ph_rutin(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	if (ph->nbr % 2 == 0)
		usleep(700);
	while (1)
	{
		if (ph->info->dead == 1)
			break ;
		eat_philo(ph);
		print(ph, "is sleeping");
		my_usleep(ph->info->time_to_sleep);
		print(ph, "is thinking");
		usleep(300);
	}
	return (0);
}

int	start_treads(t_data *d)
{
	int	i;

	i = 0;
	d->forks = malloc(sizeof(pthread_mutex_t) * d->number_of_philo);
	if (d->forks == NULL)
	{
		write(2, "Malloc error\n", 13);
		return (1);
	}
	while (i < d->number_of_philo)
		pthread_mutex_init(&(d->forks[i++]), NULL);
	pthread_mutex_init(&(d->mut_print), NULL);
	d->threads = malloc(sizeof(pthread_t) * d->number_of_philo);
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
