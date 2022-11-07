#include "philo.h"

static void	eat_philo(t_philo *ph)
{
	pthread_mutex_lock(&(ph->info->forks[ph->r_fork - 1]));
	print(ph, "has taken a fork");
	pthread_mutex_lock(&(ph->info->forks[ph->l_fork - 1]));
	print(ph, "has taken a fork");
	pthread_mutex_lock(&(ph->info->mut_t));
	ph->last_meal_time = get_time();
	pthread_mutex_unlock(&(ph->info->mut_t));
	print(ph, "is eating");
	my_usleep(ph->info->time_to_eat);
	pthread_mutex_unlock(&(ph->info->forks[ph->l_fork - 1]));
	pthread_mutex_unlock(&(ph->info->forks[ph->r_fork - 1]));
	pthread_mutex_lock(&(ph->info->mut_e));
	ph->eat_count++;
	pthread_mutex_unlock(&(ph->info->mut_e));
}

void	*ph_rutin(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	if (ph->nbr % 2 == 0)
		usleep(700);
	while (1)
	{
		eat_philo(ph);
		print(ph, "is sleeping");
		my_usleep(ph->info->time_to_sleep);
		print(ph, "is thinking");
		usleep(300);
	}
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
	pthread_mutex_init(&(d->mut_e), NULL);
	pthread_mutex_init(&(d->mut_t), NULL);
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
