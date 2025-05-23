/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 13:47:13 by tkeil             #+#    #+#             */
/*   Updated: 2025/04/08 18:15:22 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_validation
{
	bool		north_tex;
	bool		south_tex;
	bool		east_tex;
	bool		west_tex;
	bool		floor;
	bool		ceiling;
	bool		tex_and_cols;
	bool		map_started;
	bool		validated;
}				t_validation;

typedef struct s_mouse
{
	bool		mouse_down;
	bool		ctrl_down;
	int			mouse_x;
	int			mouse_y;
}				t_mouse;

typedef struct s_img
{
	void		*img;
	char		*data;
	int			linelen;
	int			bpp;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef struct s_texture
{
	void		*img;
	char		*data;
	int			linelen;
	int			bpp;
	int			endian;
	int			width;
	int			height;
}				t_texture;

typedef struct s_slice
{
	int			y_start;
	int			y_end;
	int			tex_x;
	int			tex_y;
	float		tex_step;
	float		tex_pos;
	t_texture	*tex;
}				t_slice;

typedef struct s_rayhit
{
	int			side;
	int			wall_h;
	int			ns_ew;
	float		wallx;
	float		distance;
	t_texture	*tex;
}				t_rayhit;

typedef struct s_keyboard
{
	bool		w_down;
	bool		a_down;
	bool		s_down;
	bool		d_down;
	bool		left_down;
	bool		right_down;
	bool		up_pressed;
	bool		down_pressed;
}				t_keyboard;

typedef struct s_dda
{
	int			mapx;
	int			mapy;
	int			stepx;
	int			stepy;
	float		sidedistx;
	float		sidedisty;
	float		deltadistx;
	float		deltadisty;
	float		perpwalldist;
}				t_dda;

typedef struct s_player
{
	float		posx;
	float		posy;
	float		dirx;
	float		diry;
	float		planex;
	float		planey;
	float		plane_length;
}				t_player;

#endif