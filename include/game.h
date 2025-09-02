/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 20:49:40 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/09/02 13:15:17 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

/***
 * floor -> Values for colors RGB
 * Ceiling -> 
 * paths -> Paths to textures
 * has_paths -> Checkers to avoid duplicated path asignation.
 */
typedef struct s_textinfo
{
	int		floor[3];
	int		ceiling[3];
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		has_no;
	int		has_so;
	int		has_we;
	int		has_ea;
	int		has_c;
	int		has_f;
} t_textinfo;



/*****************************************************************
 * Main structure with the game info
 * textures		->
 * floor		-> floor color
 * ceiling		-> ceiling color
 * spawn_x		->
 * spawn_y		->
 * spawn_dir	-> The direction of the camera; // 'N', 'S', 'E', 'W'*
 *****************************************************************/
typedef struct s_game
{
	t_textinfo	*textures;
	char		**map;
	int			spawn_x;
	int			spawn_y;
	char		spawn_dir;
	int			max_col;
	int			max_row;
} t_game;



# endif