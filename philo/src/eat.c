/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabou <tbabou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:23:53 by tbabou            #+#    #+#             */
/*   Updated: 2024/12/13 03:59:12 by tbabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	check_full(t_philo *philo)
{
	pthread_mutex_lock(&philo->program->lock);
	if (philo->program->no_meals == philo->no_eaten)
		philo->program->no_full += 1;
	pthread_mutex_unlock(&philo->program->lock);
}

static int	grap_forks(t_philo *philo)
{
	if (check_stop(philo))
		return (1);
	pthread_mutex_lock(philo->l_fork);
	print_lock(philo, "has taken a fork", 0);
	pthread_mutex_lock(philo->r_fork);
	print_lock(philo, "has taken a fork", 0);
	if (check_stop(philo))
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return (1);
	}
	return (0);
}

int	eat(t_philo *philo)
{
	if (check_stop(philo))
		return (1);
	if (grap_forks(philo))
		return (1);
	print_lock(philo, "is eating", 0);
	pthread_mutex_lock(&philo->program->lock);
	philo->last_eat = get_current_time() - philo->program->start_time;
	pthread_mutex_unlock(&philo->program->lock);
	if (wait(philo->program->eat_time, philo))
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return (1);
	}
	philo->no_eaten += 1;
	check_full(philo);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (0);
}
