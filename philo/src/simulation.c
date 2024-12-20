/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabou <tbabou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 14:12:13 by tbabou            #+#    #+#             */
/*   Updated: 2024/12/13 04:03:54 by tbabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	check_starvation(t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(&philo->program->lock);
	if (philo->program->stop != 1)
	{
		time = get_current_time() - philo->program->start_time;
		if (time - philo->last_eat > philo->program->die_time)
		{
			pthread_mutex_unlock(&philo->program->lock);
			print_lock(philo, "died", 1);
			return (1);
		}
	}
	pthread_mutex_unlock(&philo->program->lock);
	return (0);
}

static int	check_philos(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->no_philos)
	{
		if (check_starvation(&program->philos[i++]))
			return (1);
	}
	return (0);
}

static	int	check_conditions(t_program *program)
{
	int	no_full;
	int	no_philos;

	if (check_philos(program))
		return (1);
	pthread_mutex_lock(&program->lock);
	no_full = program->no_full;
	no_philos = program->no_philos;
	pthread_mutex_unlock(&program->lock);
	if (no_full == no_philos)
	{
		pthread_mutex_lock(&program->lock);
		program->stop = 1;
		pthread_mutex_unlock(&program->lock);
		return (1);
	}
	return (0);
}

void	monitor_simulation(t_program *program)
{
	while (1)
	{
		if (check_conditions(program))
		{
			break ;
		}
	}
	join_threads(program, program->no_philos);
	cleanup(program);
}

void start_simulation(t_program *program)
{
    int i;
    int error;

    i = 0;
    pthread_mutex_lock(&program->lock);
    while (i < program->no_philos)
    {
        error = pthread_create(&program->philos[i].t, NULL,
                    &routine, (void *)&program->philos[i]);
        if (error)
        {
            program->stop = 1;
            pthread_mutex_unlock(&program->lock);
            join_threads(program, i);
            cleanup(program);
            printf("Failed to create thread");
            exit(1);
        }
        i++;
    }
    program->start_time = get_current_time();
    program->start = 1;
    pthread_mutex_unlock(&program->lock);
}
