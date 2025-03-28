/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkeil <tkeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:16:28 by tkeil             #+#    #+#             */
/*   Updated: 2025/03/29 20:37:13 by tkeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int ft_check_textures_and_colors(t_validation *checks, char *line)
{
    char    **split;

    if (checks->map_started && !checks->tex_and_cols)
        return (ft_err_message("Error\n", "Map started before Textures and colors were parsed!"), 0);
    split = ft_split(line, ' ');
    if (!split)
        return (0);
    if (!ft_check_textures(checks, split) || !ft_check_colors(checks, split))
        return (ft_free_ptr(&split), 0);
    return (ft_free_ptr(&split), 1);
}

static int  ft_validate_cub_format(char *file)
{
    int             fd;
    char            *line;
    t_validation    checks;

    if (ft_open_file(file, &fd) == -1)
        return (0);
    ft_init_checks(&checks);
    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break ;
        checks.map_started = ft_is_line_of_map(line);
        if (!ft_check_textures_and_colors(&checks, line))
            break ;
        ft_update_check_tex_and_cols(&checks);
        if (checks.tex_and_cols && checks.map_started)
        {
            if (!ft_check_map(file, line, fd))
                break ;
            checks.validated = true;
        }
        ft_free(&line);
    }
    return (close(fd), ft_free(&line), checks.validated);
}

int ft_validate_cub_file(char *file)
{
    char    *format;

    if (ft_strlen(file) < 5)
    {
        write(STDERR_FILENO, "Error\n", 6);
        return (ft_err_message(file, ": invalid .cub filename"), 0);
    }
    format = file + (ft_strlen(file) - 4);
    if (ft_strncmp(format, ".cub", 4) != 0)
    {
        write(STDERR_FILENO, "Error\n", 6);
        return (ft_err_message(file, ": invalid .cub file extension"), 0);
    }
    if (!ft_validate_cub_format(file))
        return (0);
    return (ft_err_message(".cub file was validated successfully!", NULL), 1);
}
