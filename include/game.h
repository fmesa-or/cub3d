/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 20:49:40 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/09/23 14:02:38 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# define TEXT_NO	0
# define TEXT_SO	1
# define TEXT_EA	2
# define TEXT_WE	3
# define TEXT_COUNT	4

/************************************************************
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


/**
 * 
 * img		->
 * addr		->
 * width	->
 * height	->
 * bpp		->
 * line_len	->
 * endian	->
 *******************/
/*typedef struct s_img_text
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;

}t_img_text;*/

//struct para MLX42
typedef struct s_img_text
{
	mlx_image_t	*img;
	int			width;
	int			height;
}t_img_text;


/***************************************************************************
 * x & y	-> Actual position in the map.                                 *
 * dirX/Y	-> Actual direction of camera.                                 *
 * planeX/Y	-> Camera plane, so we can calculate the size of the viewfield.*
 **************************************************************************/
typedef struct s_player
{
	int		x;
	int		y;
	int		dirX;
	int		dirY;
	int		planeX;
	int		planeY;
} t_player;

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