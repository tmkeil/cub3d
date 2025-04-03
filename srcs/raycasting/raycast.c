/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 16:51:40 by tkeil             #+#    #+#             */
/*   Updated: 2025/04/03 01:57:10 by tkeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_raycast(t_data **data)
{
    int     x;
    float   incr;
    float   section[(*data)->wnd_w];
    
    ft_clean_window(*data);
    x = 0;
    incr = (FOV / 2) - (FOV / (*data)->wnd_w - 1) * (180 / M_PI);
    while (x < (*data)->wnd_w)
    {
        section[x] = incr * x - (*data)->player.angle;
        x++;
    }
    x = 0;
    while (x < (*data)->wnd_w)
    {
        ft_draw_wall_slice(*data, (*data)->buffer, section, x);
        x++;
    }
	return (1);
}
