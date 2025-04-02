/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 19:34:52 by tkeil             #+#    #+#             */
/*   Updated: 2025/04/01 20:07:05 by tkeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	ft_get_position_and_direction(char **map, float *px, float *py)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E'
				|| map[y][x] == 'W')
			{
				*px = x;
				*py = y;
				return (map[y][x]);
			}
			x++;
		}
		y++;
	}
	return ('N');
}

void	ft_init_player(t_data **data, char **map)
{
	char	orientation;

	orientation = ft_get_position_and_direction(map, &(*data)->player.x,
			&(*data)->player.y);
	if (orientation == 'N')
		(*data)->player.angle = 0;
	if (orientation == 'S')
		(*data)->player.angle = M_PI;
	if (orientation == 'E')
		(*data)->player.angle = M_PI_2;
	if (orientation == 'W')
		(*data)->player.angle = -M_PI_2;
}

void	ft_init_keyboard(t_data **data)
{
	(*data)->keyboard.w_down = false;
	(*data)->keyboard.a_down = false;
	(*data)->keyboard.s_down = false;
	(*data)->keyboard.d_down = false;
}
