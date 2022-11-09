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
		philos[i].data = data;
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
	data->dead = 0;
	return (data);
}
