/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/07/13 12:14:43 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	error(char *str)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	return (ERROR);
}

int	error_free(char *str, t_data *data)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	free_stuff(data);
	return (ERROR);
}

int	error_semaphore(char *str, t_data *data)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	close_semaphore(data->s_forks, "FORKS");
	close_semaphore(data->s_write, "WRITE");
	free_stuff(data);
	return (ERROR);
}

int	error_exit(char *str)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	exit(ERROR);
}

int	general_error(t_data *data, char *str)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	kill_processes(data);
	free_stuff(data);
	exit(ERROR);
}
