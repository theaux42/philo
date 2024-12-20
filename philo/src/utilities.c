/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabou <tbabou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:50:58 by tbabou            #+#    #+#             */
/*   Updated: 2024/12/17 12:10:53 by tbabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_lock(t_philo *philo, char *msg, int flag)
{
	size_t	time;

	pthread_mutex_lock(&philo->program->lock);
	if (flag)
	{
		philo->program->stop = 1;
		time = get_current_time() - philo->program->start_time;
		printf("%zu %d %s\n", time, philo->id, msg);
	}
	if (philo->program->stop)
	{
		pthread_mutex_unlock(&philo->program->lock);
		return ;
	}
	time = get_current_time() - philo->program->start_time;
	printf("%zu %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->program->lock);
}

int	check_stop(t_philo *philo)
{
	pthread_mutex_lock(&philo->program->lock);
	if (philo->program->stop)
	{
		pthread_mutex_unlock(&philo->program->lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->program->lock);
	return (0);
}

int	wait(size_t ms, t_philo *philo)
{
	size_t	str;

	str = get_current_time();
	while ((get_current_time() - str) < ms)
	{
		usleep(500);
		if (check_stop(philo))
			return (1);
	}
	return (0);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
