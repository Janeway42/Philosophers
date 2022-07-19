/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   surveillance.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/07/19 15:01:45 by janeway       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	kill_processes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nr_philo)
	{
		if (kill(data->process_id[i], SIGKILL) > 0)
			return (ERROR);
		i++;
	}
	return (OK);
}

int	surveillance(t_data *data)
{
	int		status;
	int		i;
	int		full;

	while (1)
	{
		i = 0;
		full = 0;
		while (i < data->nr_philo)
		{
			waitpid(-1, &status, 0);
			if (WIFEXITED(status) && WEXITSTATUS(status) == DEAD)
				return (kill_processes(data));
			if (WIFEXITED(status) && WEXITSTATUS(status) == FULL)
				if (full++ == data->nr_philo)
					return (kill_processes(data));
			if (WIFEXITED(status) && WEXITSTATUS(status) == ERROR)
				return (general_error(data, "error exit\n"));
			i++;
			usleep(1000);
		}
	}
	return (OK);
}
