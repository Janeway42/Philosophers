/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_data.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/07/08 17:27:34 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	choose_forks(t_data *data, int i)
{
	if (data->philos[i].id % 2 != 0)
	{
		data->philos[i].left_fork = data->philos[i].id;
		data->philos[i].right_fork = data->philos[i].id - 1;
		if (data->philos[i].right_fork == -1)
			data->philos[i].right_fork = data->nr_philo - 1;
	}
	else if (data->philos[i].id % 2 == 0)
	{
		data->philos[i].left_fork = data->philos[i].id - 1;
		if (data->philos[i].left_fork == -1)
			data->philos[i].left_fork = data->nr_philo - 1;
		data->philos[i].right_fork = data->philos[i].id;
	}
}

int	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nr_philo)
	{
		data->philos[i].id = i;
		choose_forks(data, i);
		data->philos[i].last_eaten = 0;
		data->philos[i].times_eaten = 0;
		data->philos[i].status = ACTIVE;
		data->philos[i].data = data;
		i++;
	}
	return (OK);
}

int	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nr_philo)
	{
		if (pthread_mutex_init(&data->forks_lock[i], NULL) != 0)
			return (error_init_mutexes(data, "init fork_locks fail\n"));
		if (pthread_mutex_init(&data->philos[i].last_meal, NULL) != 0)
			return (error_init_mutexes(data, "init last_meal fail\n"));
		i++;
	}
	if (pthread_mutex_init(&data->dead_monitor, NULL) != 0)
		return (error_init_mutexes(data, "init dead_monitor fail\n"));
	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
		return (error_init_mutexes(data, "init write_lock fail\n"));
	return (OK);
}

int	init_data(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->nr_philo);
	if (!data->philos)
		return (error("malloc fail\n"));
	data->forks_lock = malloc(sizeof(pthread_mutex_t) * data->nr_philo);
	if (!data->forks_lock)
		return (error_forks(data, "malloc fail\n"));
	if (init_mutexes(data) == ERROR)
		return (ERROR);
	if (init_philo(data) == ERROR)
		return (ERROR);
	data->dead_philo = 0;
	if (gettimeofday(&data->start_time, NULL) != 0)
		return (ERROR);
	return (OK);
}
