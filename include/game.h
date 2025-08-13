/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 20:49:40 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/08/13 21:32:33 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

/***
 * 
 */
typedef struct s_color
{
	int	r;
	int	g;
	int	b;
} t_color;

/***
 * 
 */
typedef struct s_textures
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
} t_textures;

/*****************************************************************
 * Main structure with the game info
 * textures ->
 * floor -> floor color
 * ceiling -> ceiling color
 * spawn_x ->
 * spawn_y ->
 * spawn_dir -> The direction of the camera; // 'N', 'S', 'E', 'W'*
 *****************************************************************/
typedef struct s_game
{
	t_textures	textures;
	t_color		floor;
	t_color		ceiling;
	char		**map;
	int			spawn_x;
	int			spawn_y;
	char		spawn_dir;
} t_game;

# endif