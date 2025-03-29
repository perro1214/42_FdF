/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhayato <hhayato@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:03:22 by perro1214         #+#    #+#             */
/*   Updated: 2025/03/29 16:17:37 by hhayato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	ft_free_map(t_map *map)
{
	int	i;
	int	j;

	if (!map)
		return ;
	if (map->array)
	{
		i = -1;
		while (++i < map->height)
		{
			if (map->array[i])
			{
				j = 0;
				while (j < map->width)
				{
					if (map->array[i][j])
						free(map->array[i][j]);
					j++;
				}
				free(map->array[i]);
			}
		}
		free(map->array);
	}
	free(map);
}

void	ft_free_env(t_fdf *env)
{
	if (!env)
		return ;
	if (env->img)
		mlx_destroy_image(env->mlx, env->img);
	if (env->win)
		mlx_destroy_window(env->mlx, env->win);
	if (env->map)
		ft_free_map(env->map);
	free(env);
}
