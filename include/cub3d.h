/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 21:01:46 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/10/20 15:08:54 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "MLX42/MLX42.h"
# include "game.h"
# include "vmem.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <math.h>
# include <limits.h>

/**********
 * COLORS *
 *********/
# define RD		"\033[1;91m"
# define PR		"\033[4;95m"
# define CI		"\033[0;96m"
# define GR		"\033[0;92m"
# define PINK	"\033[0;94m"
# define FF		"\033[0;97m"
# define RES	"\033[0m"

/***********************************
 * Integers needed for parse_map.c *
 **********************************/
typedef struct s_flies
{
	int	i;
	int	j;
	int	start;
	int	line_len;
	int	player_count;
}	t_flies;

/***************
 * FILE READER *
 **************/
char		**read_file(const char *filename);

/*******
 * GNL *
 ******/
char		*get_next_line(int fd);
char		*gnl_strjoin(char *s1, char *s2);
int			gnl_jumpfinder(char *backup);

/***********
 * LIBFT   *
 **********/
int			ft_strlen(char *s);
char		*ft_strchr(char *s, int c);
void		ft_sfree_split(char **array);
char		**ft_split(char const *s, char c);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
int			ft_isspace(char c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

/***********
 * ERROR   *
 **********/
void		error_msg(char *msg);

/**************
 * CHECK FILE *
 *************/
void		check_file(char *av);
void		check_extension(char *file_name);

/******************************
 * MAP PARSING AND VALIDATION *
 *****************************/
void		cu_parse_map(char **file, int start);
void		check_and_parse_file(char *file_name, t_data *data);
void		validate_map(void);
void		check_and_parse_file(char *file_name, t_data *data);
void		parse_textures(char **map_array, t_textinfo *tex, int *i);
int			parse_rgb_line(char *line, int rgb[3]);
void		init_textinfo(t_textinfo *info);
void		cu_checkmap(t_data *data);
int			check_png(char *path);
int			ft_atoi_rgb(const char *str);
int			valid_rgb_value(int n);
int			check_tex_path(char *path);
int			valid_tex(char *path);
char		*get_texture_path(char *line, int j);
void		cu_savemap(char **file, int start);
void		check_player_pos(t_game *game);
void		save_player_pos(int i, int j, char dir, t_game *game);
void		check_and_parse_file(char *file_name, t_data *data);
void		cu_filledmaper(t_game game);
void		load_text(t_data *data);
uint32_t	get_hex_color(int rgb[3]);
void		final_tex_check(t_textinfo *tex);

/*************
 * EXECUTION *
 ************/
void		cu_init_player(t_player *player, t_game *game);
void		cu_cast_rays(t_data *data, mlx_image_t *screen);
void		cu_picasso(t_data *dat, mlx_image_t *scrn, int x, mlx_image_t *txt);

/*********
 * HOOKS *
 ********/
void		key_hook(mlx_key_data_t keydata, void *param);
void		handle_key_release(t_game *game, int key);
void		handle_key_press(t_game *game, int key);

/*****************
 * MOVEMENT LOOP *
 ****************/
void		movement_loop(void *param);
int			process_movement(t_data *data, double delta_time);
int			process_rotation(t_data *data, double delta_time);

/**********************
 * MOVEMENT FUNCTIONS *
 *********************/
void		move_forward(t_data *data, double delta_time);
void		move_backward(t_data *data, double delta_time);
void		strafe_left(t_data *data, double delta_time);
void		strafe_right(t_data *data, double delta_time);
void		look_left(t_data *data, double delta_time);
void		look_right(t_data *data, double delta_time);

/******************
 * MOVEMENT UTILS *
 *****************/
int			check_wall_collision(t_data *data, double new_x, double new_y);
void		move_player_safe(t_data *data, double new_x, double new_y);
void		rotate_player(t_data *data, double angle);

#endif