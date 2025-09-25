/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 20:49:40 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/09/25 12:30:06 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

/************************************************************
 * TEXTURES VALUES                                          *
 *                                                          *
 * Asigns a number for each texture to simplify when called.*
 * TEXT_COUNT	-> Total number of posible textures.        *
 ***********************************************************/
# define TEXT_NO	0
# define TEXT_SO	1
# define TEXT_EA	2
# define TEXT_WE	3
# define TEXT_COUNT	4

/***********************************************
 * SPECS                                       *
 *                                             *
 * S_WITH/S_HEIGHT	-> Screen width and height.*
 * WALL_SIZE		-> The size of the wall.   *
 * FOV				-> Field of view.          *
 * R_SPEED			-> Rotation Speed.         *
 * P_SPEED			-> Player Speed.           *
 **********************************************/
# define S_WIDTH		3000
# define S_HEIGHT		1800
# define WALL_SIZE		30
# define FOV			60
# define R_SPEED		0.045
# define P_SPEED		4

/************************************************************
 * TEXTURE INFO.                                            *
 *                                                          *
 * floor -> RGB value for floor color                       *
 * Ceiling -> RGB value for ceiling color                   *
 * paths -> Paths to textures                               *
 * has_paths -> Checkers to avoid duplicated path asignation*
 ***********************************************************/
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
	int		has_ea;
	int		has_we;
	int		has_c;
	int		has_f;
} t_textinfo;

/**************************************
 * IMAGE TEXTURE                      *
 *                                    *
 * img		-> Pointer to the texture.*
 * width	-> Width in pixels.       *
 * height	-> Height in pixels.      *
 *************************************/
typedef struct s_img_text
{
	mlx_image_t	*img;
	int			width;
	int			height;
} t_img_text;

/***************************************************************************
 * PLAYER                                                                  *
 *                                                                         *
 *  x & y	-> Actual position in the map.                                 *
 * dirX/Y	-> Actual direction of camera.                                 *
 * planeX/Y	-> Camera plane, so we can calculate the size of the viewfield.*
 **************************************************************************/
typedef struct s_player
{
	double		x;
	double		y;
	double		dirX;
	double		dirY;
	double		planeX;
	double		planeY;
} t_player;

/*********************************************************************
 * MAIN STRUCTURE                                                    *
 *                                                                   *
 * textures		-> Stored texture info and paths.                    *
 * img_text		-> All the textures images in one array.             *
 * map			-> Double array with 0 & 1 to save a map.            *
 * spawn_x		-> Spawn coordinate for axis X.                      *
 * spawn_y		-> Spawn coordinate for axis Y.                      *
 * spawn_dir	-> The direction of the camera; // 'N', 'S', 'E', 'W'*
 * max_col/row	-> Value with the total number of columns/rows.      *
 * player		-> Struct with player info.                          *
 ********************************************************************/
typedef struct s_game
{
	t_textinfo	*textures;
	t_img_text	img_text[TEXT_COUNT];
	char		**map;
	int			spawn_x;
	int			spawn_y;
	char		spawn_dir;
	int			max_col;
	int			max_row;
	t_player	player;
} t_game;

# endif