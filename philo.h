#ifndef PHILO_H
#define PHILO_H
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>


struct s_data;

typedef struct s_philo
{
    int				nbr;
	int				eat_count;
	long long int	last_meal_time;
	int				l_fork;
	int				r_fork;
    pthread_t		thr_id;
	struct s_data	*info;
}       t_philo;

typedef struct s_data
{
    t_philo         *philo;
    int             number_of_philo;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             nb_of_t_each_ph_must_e;
    long long       start;
    pthread_t		*threads;
    pthread_mutex_t *forks;
    pthread_mutex_t	mut_print;
	pthread_mutex_t	mut_t;
	pthread_mutex_t	mut_e;
}       t_data;


int check_arg(int ac, char **av);
int parsing(int ac, char **av, int *data);
int	if_zero(int ac, int *data);
void	my_usleep(long long time);
int	print(t_philo *ph, char *str);
long long int	get_time(void);
void	free_and_destroy(t_data *data);
int	check_end(t_data *data);
t_data	*init_data(int argc, int *arg);
int	start_treads(t_data *d);
void	*ph_rutin(void *philo);
int	ft_atoi(const char *str);

#endif