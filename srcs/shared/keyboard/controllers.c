/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controllers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:33:39 by tkeil             #+#    #+#             */
/*   Updated: 2025/04/11 17:18:56 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_mouse_down(int button, int x, int y, void *param)
{
	t_data	*data;

	(void)x;
	(void)y;
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

int	ft_mousemove(int x, int y, t_data *data)
{
	float		delta_x;
	float		delta_y;
	static int	old_x = -1;
	static int	old_y = -1;

	old_x = x * (old_x == -1) + old_x * (old_x != -1);
	old_y = y * (old_y == -1) + old_y * (old_y != -1);
	delta_x = x - old_x;
	delta_y = old_y - y;
	if (x >= 0 && x <= data->wnd_w && y >= 0 && y <= data->wnd_h
		&& !data->mouse.mouse_down)
	{
		if (delta_x != 0)
			ft_rotate(&data->player, delta_x * ROTATION_SPEED);
		if (delta_y != 0 && delta_y > 0 && data->center_h < data->wnd_h)
			data->center_h += delta_y * 2;
		else if (delta_y != 0 && delta_y < 0
			&& data->center_h > 0)
		{
			data->center_h += delta_y * 2;
		}
	}
	return (old_x = x, old_y = y, 0);
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
		data->keyboard.left_down = false;
	else if (key == RIGHT)
		data->keyboard.right_down = false;
	else if (key == UP)
		data->keyboard.up_pressed = false;
	else if (key == DOWN)
		data->keyboard.down_pressed = false;
	return (0);
}

int	ft_keydown(int key, void *param)
{
	t_data	**data;

	data = (t_data **)&param;
	if (key == W)
		(*data)->keyboard.w_down = true;
	else if (key == A)
		(*data)->keyboard.a_down = true;
	else if (key == S)
		(*data)->keyboard.s_down = true;
	else if (key == D)
		(*data)->keyboard.d_down = true;
	else if (key == LEFT)
		(*data)->keyboard.left_down = true;
	else if (key == RIGHT)
		(*data)->keyboard.right_down = true;
	else if (key == UP)
		(*data)->keyboard.up_pressed = true;
	else if (key == DOWN)
		(*data)->keyboard.down_pressed = true;
	return (0);
}
