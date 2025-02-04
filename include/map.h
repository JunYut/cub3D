/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:54:34 by we                #+#    #+#             */
/*   Updated: 2025/02/04 16:12:34 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

typedef struct s_list	t_list;
typedef struct s_img	t_img;

typedef struct s_texture
{
	t_img	*img;
	char	*path;
	int		width;
	int		height;
}	t_texture;

// `texture` is stored in N, S, E, W order
// `floor` and `ceiling` are stored in R, G, B order
// `spawn` is stored in x, y, direction order
typedef struct s_map
{
	t_list		*map;
	t_texture	texture[4];
	int			fc_rgb[2][3];
	int			spawn[3];
	int			width;
	int			height;
}	t_map;

t_map	*parse_map(int file, void *mlx);
t_list	*load_file(int file);
t_list	*get_texture_path(t_list *raw, t_texture *texture);
t_list	*get_rgb(t_list *raw, int (*rgb)[3]);
void	get_map(t_list *raw, t_list **map, int *width, int *height);
void	get_spawn(t_list *map, int *spawn);
void	load_textures(t_texture *texture, void *mlx);

void	validate_map(t_map *map);
void	valid_texture_path(t_texture *texture);
void	valid_iden(t_list *map);
void	valid_walls(t_list *map);

void	count_cfg(t_list *raw, int count, char *msg);
char	**split_cfg(char *line);

void	print_texture_path(t_texture *texture);
void	print_rgb(int (*rgb)[3]);
void	print_spawn(int *spawn);
void	print_map(t_list *map);

#endif
