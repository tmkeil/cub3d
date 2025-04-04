/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_allocations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:32:59 by tkeil             #+#    #+#             */
/*   Updated: 2025/04/04 15:19:32 by tkeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int    ft_init_window(t_data **data)
{
    int		h;
	int		w;
    void	*mlx;

    mlx = (*data)->mlx_ptr;
	h = (*data)->wnd_h * ((*data)->wnd_h > 0) + HEIGHT * ((*data)->wnd_h == 0);
	w = (*data)->wnd_w * ((*data)->wnd_w > 0) + WIDTH * ((*data)->wnd_w == 0);
    (*data)->mlx_win = mlx_new_window(mlx, w, h, "cub3D");
    if (!(*data)->mlx_win)
        return (0);
    (*data)->wnd_w = w;
    (*data)->wnd_h = h;
    return (1);     
}

int    ft_init_image(t_data **data)
{
    int     w;
    int		h;
    void	*mlx;
    t_img	*img;

    mlx = (*data)->mlx_ptr;
    w = (*data)->wnd_w;
    h = (*data)->wnd_h;
    (*data)->buffer = malloc(sizeof(t_img));
	if (!(*data)->buffer)
		return (0);
	img = (*data)->buffer;
	img->img = mlx_new_image(mlx, w, h);
	if (!img->img)
		return (0);
	img->data = mlx_get_data_addr(img->img, &img->bpp, &img->linelen,
			&img->endian);
	if (!img->data)
		return (0);
    img->width = w;
    img->height = h;
    return (1);     
}

static int	ft_create_textures(t_data **data)
{
	(*data)->north = malloc(sizeof(t_texture));
	(*data)->south = malloc(sizeof(t_texture));
	(*data)->east = malloc(sizeof(t_texture));
	(*data)->west = malloc(sizeof(t_texture));
	if (!(*data)->east || !(*data)->west || !(*data)->north || !(*data)->south)
		return (0);
	(*data)->north->img = NULL;
	(*data)->south->img = NULL;
	(*data)->east->img = NULL;
	(*data)->west->img = NULL;
	return (1);
}

int	ft_create_map(t_data **data, char *file)
{
	int		fd;
	size_t	i;

	if (ft_open_file(file, &fd) == -1)
		return (0);
	(*data)->map = ft_get_map(file, fd);
	if (!(*data)->map)
		return (0);
	i = 0;
	while ((*data)->map[i])
		i++;
	(*data)->map_height = i;
	return (1);
}

int	ft_initialization(t_data **data, char *file)
{
	*data = malloc(sizeof(t_data));
	if (!*data)
		return (0);
	ft_init_null(data);
	(*data)->mlx_ptr = mlx_init();
	if (!(*data)->mlx_ptr)
		return (0);
	if (!ft_init_window(data) || !ft_init_image(data))
		return (0);
	if (!ft_create_textures(data))
		return (0);
	if (!ft_create_map(data, file))
		return (0);
	ft_init_keyboard(data);
	ft_init_player(data, (*data)->map);
	return (1);
}
