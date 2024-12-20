/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabou <tbabou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:06:39 by tbabou            #+#    #+#             */
/*   Updated: 2024/12/13 03:59:12 by tbabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	init_philo(t_philo *philo, t_program *program, int i)
{
	philo->program = program;
	philo->l_fork = &program->forks[i];
	philo->r_fork = &program->forks[(i + 1) % program->no_philos];
	philo->id = i + 1;
	philo->no_eaten = 0;
	philo->last_eat = 0;
}

static int	init_mutexes(t_program *program)
{
	int	i;

	if (pthread_mutex_init(&program->lock, NULL))
		return (1);
	i = 0;
	program->forks = malloc(sizeof(pthread_mutex_t) * program->no_philos);
	if (!program->forks)
	{
		pthread_mutex_destroy(&program->lock);
		return (1);
	}
	while (i < program->no_philos)
	{
		if (pthread_mutex_init(&program->forks[i], NULL))
		{
			while (i > 0)
				pthread_mutex_destroy(&program->forks[--i]);
			pthread_mutex_destroy(&program->lock);
			free(program->forks);
			return (1);
		}
		i++;
	}
	return (0);
}

int	init(t_program *program)
{
	int	i;

	i = 0;
	program->no_full = 0;
	program->stop = 0;
	program->start = 0;
	program->philos = malloc(program->no_philos * sizeof(t_philo));
	if (!program->philos)
	{
		error("Initializing array of philosophers structs failed");
		return (1);
	}
	if (init_mutexes(program))
	{
		free(program->philos);
		error("Initializing array of mutexes failed");
		return (1);
	}
	while (i < program->no_philos)
	{
		init_philo(&program->philos[i], program, i);
		i++;
	}
	return (0);
}
