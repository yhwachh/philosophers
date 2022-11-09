/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibalbako <ibalbako@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:42:24 by ibalbako          #+#    #+#             */
/*   Updated: 2022/11/07 11:42:25 by ibalbako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_arg(int ac, char **av)
{
    int i;
    int j;

    i = 1;
    j = 0;
    while (i < ac)
    {
        j = 0;
        while (av[i][j] && av[i][j] == 32)
            j++;
        if (av[i][j] == '-')
        {
            write(2, "Error\n", 6);
            return (1);
        }
        i++;
    }
    return(0);
}

static int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	return (0);
}

int parsing(int ac, char **av, int *data)
{
    int	i;
	int	j;

	i = 0;
	while (++i < ac)
	{
		j = 0;
		while (av[i][j] && av[i][j] == 32)
			j++;
		while (av[i][j] && ft_isdigit(av[i][j]) == 1)
			j++;
		if (av[i][j] != 0)
		{
			write(2, "Error\n", 6);
			return (1);
		}
		data[i - 1] = ft_atoi(av[i]);
		if (data[i - 1] == -1)
		{
			write(2, "Error\n", 6);
			return (1);
		}
	}
	return (0);

}
int	if_zero(int ac, int *data)
{
	if (data[0] == 0)
	{
		free(data);
		write(2, "Error\n", 6);
		return (1);
	}
	else if (data[1] == 0)
	{
		free(data);
		write(2, "Error\n", 6);
		return (1);
	}
	if (ac == 6 && data[4] == 0)
	{
		free(data);
		write(2, "Error\n", 6);
		return (1);
	}
	return (0);
}

int main(int argc, char **argv)
{
    t_data *data;
    int     *tmp;

    if (argc != 5 && argc != 6)
    {
        write(2, "Error\n", 6);
        return (1);
    }
    check_arg(argc, argv);
    tmp = (int *)malloc(sizeof(int) * (argc - 1));
    if (parsing(argc,argv,tmp) == 1)
    {
        free(tmp);
        return (1);
    }
    if (if_zero(argc, tmp) == 1)
		return (1);
    data = init_data(argc, tmp);
    if (data == NULL)
        return(1);
    free(tmp);
    if (treads(data) == 0)
		if_end(data);
	free_all_and_destroy(data);
	return (0);
}
