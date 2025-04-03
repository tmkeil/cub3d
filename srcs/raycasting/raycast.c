/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 16:51:40 by tkeil             #+#    #+#             */
/*   Updated: 2025/04/03 22:54:25 by tkeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void ft_update_players_pos_and_dir(t_data **data, float angle)
{
	if ((*data)->keyboard.w_down)
	{
		printf("w movement\n");
		(*data)->player.x += cos(angle) * SPEED;
		(*data)->player.y += sin(angle) * SPEED;
	}
	if ((*data)->keyboard.a_down)
	{
		(*data)->player.x -= cos(angle) * SPEED;
		(*data)->player.y -= sin(angle) * SPEED;
	}
	if ((*data)->keyboard.s_down)
	{
		(*data)->player.x += cos(angle - M_PI_2) * SPEED;
		(*data)->player.y += sin(angle - M_PI_2) * SPEED;
	}
	if ((*data)->keyboard.d_down)
	{
		(*data)->player.x += cos(angle + M_PI_2) * SPEED;
		(*data)->player.y += sin(angle + M_PI_2) * SPEED;
	}
}

// incr = (30) - 29.xxx in rad
// (30) to (-30) => ((FOV / 2) - x * (FOV / (*data)->wnd_w - 1))
// if player dir = north (90 degrees) && FOV = 60 degrees => section[0] = 120 degrees && section[width - 1] = 60 degrees. (In radiant).
int	ft_raycast(t_data **data)
{
    int     x;
    float   incr;
    float   fov_rad_2;
    float   section[(*data)->wnd_w];

	// printf("in the raycastin fun. (*data)->wnd_w = %i\n", (*data)->wnd_w);
    ft_clean_window(*data);
    ft_update_players_pos_and_dir(data, (*data)->player.angle);
    x = 0;
    // fov_rad_2 = (FOV * (180 / M_PI)) / 2;
	fov_rad_2 = ((float)FOV / 2) * (M_PI / 180);
    incr = ((float)FOV / ((*data)->wnd_w - 1)) * (M_PI / 180);
	// printf("before incr loop (*data)->player.angle = %f, incr = %f\n", (*data)->player.angle * (180 / M_PI), incr);
    while (x < (*data)->wnd_w)
    {
        section[x] = (fov_rad_2 - incr * x) + (*data)->player.angle;
		// printf("section[%i] = %f rad and %f degrees\n", x, section[x], section[x] * 180 / M_PI);
        x++;
    }
    x = 0;
    while (x < (*data)->wnd_w)
    {
		printf("before draw wall\n");
        ft_draw_wall_slice(*data, &(*data)->buffer, section, x);
		printf("after draw wall\n\n");
        x++;
    }
	ft_putpxl(&(*data)->buffer, 5, 5, 0xff0000);
	mlx_put_image_to_window((*data)->mlx_ptr, (*data)->mlx_win, (*data)->buffer->img, 0, 0);
	return (1);
}
