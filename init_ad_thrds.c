#include "philo.h"

static t_philo	*init_philo(t_data *data)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = (t_philo *)malloc(sizeof(t_philo) * data->number_of_philo);
	while (i < data->number_of_philo)
	{
		philos[i].nbr = i + 1;
		philos[i].eat_count = 0;
		philos[i].last_meal_time = data->start;
		philos[i].r_fork = i + 2;
		philos[i].l_fork = i + 1;
		if (i == data->number_of_philo - 1)
		{
			philos[i].l_fork = 1;
			philos[i].r_fork = i + 1;
		}
		philos[i].info = data;
		i++;
	}
	return (philos);
}

t_data	*init_data(int argc, int *arg)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	data->number_of_philo = arg[0];
	data->time_to_die = arg[1];
	data->time_to_eat = arg[2];
	data->time_to_sleep = arg[3];
	if (argc == 6)
		data->nb_of_t_each_ph_must_e = arg[4];
	else
		data->nb_of_t_each_ph_must_e = -1;
	data->start = get_time();
	data->philo = init_philo(data);
	return (data);
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
