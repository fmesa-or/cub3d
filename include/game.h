/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 00:34:02 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/10/20 17:03:48 by fmesa-or         ###   ########.fr       */
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
# define TEXT_NO		0
# define TEXT_SO		1
# define TEXT_EA		2
# define TEXT_WE		3
# define TEXT_COUNT		4

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
# define R_SPEED		1.5
# define P_SPEED		3.0

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
	int					floor[3];
	int					ceiling[3];
	char				*no_path;
	char				*so_path;
	char				*we_path;
	char				*ea_path;
	int					has_no;
	int					has_so;
	int					has_ea;
	int					has_we;
	int					has_c;
	int					has_f;
}	t_textinfo;

/**************************************
 * IMAGE TEXTURE                      *
 *                                    *
 * img		-> Pointer to the texture.*
 * width	-> Width in pixels.       *
 * height	-> Height in pixels.      *
 *************************************/
typedef struct s_img_text
{
	mlx_image_t			*img;
	int					width;
	int					height;
}	t_img_text;

/*******************************************************************************
 * RAYS                                                                        *
 *                                                                             *
 * raydir_x/Y		-> The direction of the ray.                               *
 * deltadist_x/Y	-> Length for crossing one unit of the grid.               *
 * sidedist_x/Y		-> Distance from current position to next grid line.       *
 * map_x/Y			-> Current grid coordinates where the ray is located.      *
 * step_x/Y			-> Direction to advance in the grid (-1 or +1).            *
 * side				-> Which wall side was hit (0=vertical, 1=horizontal).     *
 * draw_start		-> Top pixel to start drawing the wall line.               *
 * draw_end			-> Bottom pixel to end drawing the wall line.              *
 * line_height		-> Height of the wall line to be drawn on screen.          *
 * perp_wall_dist	-> Perpendicular distance to the wall to avoid fisheye fx. *
 ******************************************************************************/
typedef struct s_ray
{
	double				raydir_x;
	double				raydir_y;
	double				deltadist_x;
	double				deltadist_y;
	double				sidedist_x;
	double				sidedist_y;
	int					map_x;
	int					map_y;
	int					step_x;
	int					step_y;
	int					side;
	int					draw_start;
	int					draw_end;
	int					line_height;
	double				perp_wall_dist;
}	t_ray;

/*******************************************************************************
 * PLAYER                                                                      *
 *                                                                             *
 *  x & y	-> Actual position in the map.                                     *
 * dir_x/Y	-> Actual direction of camera.                                     *
 * plane_x/Y	-> Camera plane, so we can calculate the size of the viewfield.*
 ******************************************************************************/
typedef struct s_player
{
	double				x;
	double				y;
	double				dir_x;
	double				dir_y;
	double				plane_x;
	double				plane_y;
}	t_player;

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
 * ray			-> Ray struct.                                       *
 * screen		-> Where we draw.                                    *
 * win_width	-> Current window width (for resize handling).       *
 * win_height	-> Current window height (for resize handling).      *
 ********************************************************************/
typedef struct s_game
{
	t_textinfo			*textures;
	t_img_text			img_text[TEXT_COUNT];
	char				**map;
	int					spawn_x;
	int					spawn_y;
	char				spawn_dir;
	int					max_col;
	int					max_row;
	t_player			player;
	t_ray				ray;
	mlx_image_t			*screen;
	int					win_width;
	int					win_height;
}	t_game;

/****************************************************
 * Struct for move_hooks.c: process_movement values.*
 ***************************************************/
typedef struct s_movement
{
	double				speed;
	double				move_x;
	double				move_y;
	double				new_x;
	double				new_y;
}	t_movement;

#endif