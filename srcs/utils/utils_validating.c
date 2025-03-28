/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 20:07:19 by tkeil             #+#    #+#             */
/*   Updated: 2025/03/28 20:08:08 by tkeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int ft_closed_horizontal(char **map, int y, int x)
{
    int     _x;
    bool    left;
    bool    right;

    _x = x;
    left = false;
    right = false;
    while (_x >=0)
    {
        if (map[y][_x--] == '1')
            left = true;
    }
    while (map[y][x])
    {
        if (map[y][x++] == '1')
            right = true;
    }
    return (left && right);
}

int ft_closed_vertical(char **map, int y, int x)
{
    int     _y;
    bool    top;
    bool    bottom;

    _y = y;
    top = false;
    bottom = false;
    while (_y >=0)
    {
        if (map[_y--][x] == '1')
            top = true;
    }
    while (map[y][x])
    {
        if (map[y++][x] == '1')
            bottom = true;
    }
    return (top && bottom);
}

// checks whether the current is blocked by a '1' vertically and horizontally
// if not, then the map is not closed by walls.
int ft_is_wall_blocked(char **map, int y, int x)
{
    return (ft_closed_horizontal(map, y, x) && ft_closed_vertical(map, y, x));
}

int ft_valid_numbers(char *s)
{
    char **cols;

    if (!s || !*s)
        return (0);
    cols = ft_split(s, ',');
    if (!cols)
        return (0);
    if (ft_ptr_len(cols) != 3)
        return (ft_free_ptr(&cols), 0);
    while (*s)
    {
        if (!ft_isdigit(*s) && *s != ' ' && !(*s >= 9 && *s <= 13))
            return (ft_free_ptr(&cols), 0);
        s++;
    }
    return (ft_free_ptr(&cols), 1);
}
