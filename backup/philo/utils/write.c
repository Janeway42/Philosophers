/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   write.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:25:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/07/18 17:03:04 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_message(t_philo *philo, enum e_msg message)
{
	const char		*prompt[] = {"has taken a fork",
		"is eating",
		"is sleeping",
		"is thinking",
		"died"};

	pthread_mutex_lock(&philo->data->write_lock);
	if (message == msg_die)
		printf("\033[0;31m%lu %d %s\033[0m\n",
			get_elapsed_time(philo), (philo->id + 1), prompt[message]);
	else if (still_alive(philo->data) == 0)
		printf("%lu %d %s\n", get_elapsed_time(philo),
			(philo->id + 1), prompt[message]);
	pthread_mutex_unlock(&philo->data->write_lock);
}
