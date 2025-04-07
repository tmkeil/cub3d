/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_slices.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 04:01:15 by tkeil             #+#    #+#             */
/*   Updated: 2025/04/07 15:20:16 by tkeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Raycasting Tutorial on: https://lodev.org/cgtutor/raycasting.html
// Casting a ray from player in rayDir.
// Using DDA for checking the grid for walls.
// Looking for wall colissions on horizontal and on vertical grid line.
//
// sideDist: distance from players position to next x/y grid line in rayDir.
// deltaDist: distance the ray travels to go from one x/y-side to the next.
// mapX/Y: current grid cell being checked for wall hit.
//
// Returns information about the perpendicular wall distance, wall side
// (N, S, E, W), that was hit and wallX (0 - 1) coordinate of the hit.
// wallX: x/y position on the wall where the ray hit (for texture alignment).
t_rayhit   ft_raytrace(t_data *data, t_player player, float *rayDir)
{
    int         side;
    t_dda       dda;

    ft_get_dda(&dda, rayDir, player);
	// printf("raztrace test\n");
	// printf("mapX, mapY = %i, %i\n", dda.mapX, dda.mapY);
	// printf("raztrace dda.sideDistX, dda.sideDistY, dda.deltaDistX, dda.deltaDistY = %f, %f, %f, %f\n", dda.sideDistX, dda.sideDistY, dda.deltaDistX, dda.deltaDistY);
    while (data->map[dda.mapY][dda.mapX] != '1')
    {
        if (dda.sideDistX < dda.sideDistY)
        {
            dda.sideDistX += dda.deltaDistX;
            dda.mapX += dda.stepX;
            side = 0;
        }
        else
        {
            dda.sideDistY += dda.deltaDistY;
            dda.mapY += dda.stepY;
            side = 1;
        }
    }
	// printf("raztrace test2\n");
    return (ft_rayhit(dda, side, rayDir, player));
}

// Raycasting Tutorial on: https://lodev.org/cgtutor/raycasting.html
// Filling the texture colors array with vertical texture color values
//
// tex_y is calculated from the current position in the wall slice.
// tex_step determines how much to move in the texture per screen pixel.
// tex_x stays constant per slice, tex_y changes with each y-pixel.
//
// If the wall was hit on a horizontal side (NS_EW == 1), the color is darkened
// to simulate lighting on the different wall sides.
void    ft_get_tex_cols(t_slice s, t_rayhit rayhit, uint32_t tex_cols[])
{
    uint32_t    color;

	(void)rayhit;
    while (s.y_start < s.y_end)
    {
        s.tex_y = (int)s.tex_pos & (s.tex->height - 1);
        s.tex_pos += s.tex_step;
		// printf("s.tex_step, s.tex_y, s.tex_pos = %f, %i, %f\n", s.tex_step, s.tex_y, s.tex_pos);
        color = s.tex->data[s.tex->linelen * s.tex_y + s.tex_x];
		// printf("nnnnnnnnn\n");
        // if (rayhit.NS_EW == 1)
        //     color = (color >> 1) & 8355711;
        tex_cols[s.y_start] = color;
		s.y_start++;
    }
}

// Raycasting Tutorial on: https://lodev.org/cgtutor/raycasting.html
// Renders one vertical slice on the screen at column x.
//
// Top: Ceiling slice, Middle: Wall slice, Bottom: Floor slice
// Wall slices are centered vertically.
//
// Wall height is based on the perpendicular distance from the player
// to the first wall hit by the ray in rayDir[x].
// So distant walls appear shorter.
//
// Texture colors are precomputed for every vertical pixel of the slice.
void    ft_draw_slice(t_data *data, t_img **img, float rayDir[][2], int x)
{
    int			y;
    t_slice     slice;
    t_rayhit    rayhit;
    uint32_t    tex_cols[data->wnd_h];
	uint32_t	color;

    rayhit = ft_raytrace(data, data->player, rayDir[x]);
    rayhit.wall_h = data->wnd_h / rayhit.distance;
	// printf("after traceing: rayhit.distance = %f, rayhit.wall_h = %i\n", rayhit.distance, rayhit.wall_h);
    ft_init_slice(data, &slice, rayhit, rayDir[x]);
	// printf("after init slice: %i, %i, %p\n", slice.y_start, slice.y_end, slice.tex);
    ft_get_tex_cols(slice, rayhit, tex_cols);
	// printf("after getting tex colors\n");
    y = 0;
    while (y < slice.y_start)
	{
		ft_putpxl(img, x, y++, data->ceiling_color);
	}
    while (y < slice.y_end)
	{
		// printf("slice pixel\n");
		(void)tex_cols;
		color = 0x9e9e9b;
		if (rayhit.NS_EW == 0)
            color = (color >> 1) & 8355711;
		ft_putpxl(img, x, y, color);
		// ft_putpxl(img, x, y, tex_cols[y]);
		y++;
	}
    while (y < data->wnd_h)
        ft_putpxl(img, x, y++, data->floor_color);
	ft_putpxl(img, 10, 10, 0xFF);
}
