/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/07/13 12:24:10 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_pthreads(t_data *data)
{
	int	i;

	i = 0;
	data->pthread_id = malloc(sizeof(pthread_t) * data->nr_philo);
	if (!data->pthread_id)
		return (error_malloc_threads(data, "failed malloc threads\n"));
	while (i < data->nr_philo)
	{
		if (pthread_create(&data->pthread_id[i], NULL,
				&routine, &data->philos[i]) != 0)
			return (error_create_threads(data, i));
		i++;
	}
	if (pthread_create(&data->surveilance, NULL,
			&dead_philo, data) != 0)
	{
		write(STDERR_FILENO, "surveilance thread fail\n", 27);
		pthread_mutex_lock(&data->dead_monitor);
		data->dead_philo = 1;
		pthread_mutex_unlock(&data->dead_monitor);
		return (ERROR);
	}
	return (OK);
}

int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nr_philo)
	{
		pthread_join(data->pthread_id[i], NULL);
		i++;
	}
	pthread_join(data->surveilance, NULL);
	return (OK);
}
