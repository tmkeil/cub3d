/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controllers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:33:39 by tkeil             #+#    #+#             */
/*   Updated: 2025/04/01 20:04:13 by tkeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_mouse_down(int button, int x, int y, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (button == 1)
		data->mouse.mouse_down = true;
	return (0);
}

int	ft_mouse_up(int key, int x, int y, void *param)
{
	t_data	*data;

	(void)x;
	(void)y;
	data = (t_data *)param;
	if (key == 1)
		data->mouse.mouse_down = false;
	return (0);
}

int	ft_mousemove(int x, int y, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	data->mouse.mouse_x = x;
	data->mouse.mouse_y = y;
	return (0);
}

int	ft_keyup(int key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (key == ESC)
		ft_destroy(data);
	if (key == W)
		data->keyboard.w_down = false;
    else if (key == A)
		data->keyboard.a_down = false;
    else if (key == S)
		data->keyboard.s_down = false;
    else if (key == D)
		data->keyboard.d_down = false;
	else if (key == LEFT)
		data->player.angle = -M_PI_2;
	else if (key == RIGHT)
		data->player.angle = M_PI_2;
	return (0);
}

int	ft_keydown(int key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
    if (key == W)
		data->keyboard.w_down = true;
    else if (key == A)
		data->keyboard.a_down = true;
    else if (key == S)
		data->keyboard.s_down = true;
    else if (key == D)
		data->keyboard.d_down = true;
	return (0);
}
