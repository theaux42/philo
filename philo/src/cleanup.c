/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabou <tbabou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 14:03:45 by tbabou            #+#    #+#             */
/*   Updated: 2024/12/13 03:59:12 by tbabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	error(char *s)
{
	printf("Error: %s \n", s);
}

void	join_threads(t_program *program, int number)
{
	int	i;

	i = 0;
	while (i < number)
	{
		pthread_join(program->philos[i].t, NULL);
		i++;
	}
}

void	cleanup(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->no_philos)
		pthread_mutex_destroy(&program->forks[i++]);
	pthread_mutex_destroy(&program->lock);
	free(program->philos);
	free(program->forks);
}
