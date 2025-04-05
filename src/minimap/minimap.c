/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:07:26 by kkhai-ki          #+#    #+#             */
/*   Updated: 2025/04/06 00:28:54 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

static void	draw_border(int x, int y, int border_color, t_img *img);
static void	draw_minimap(t_fpoint map, int range, \
				t_map *map_data, t_vars *vars);
static int	get_pixel_color(t_point tile, t_fpoint pixel, \
				t_map *map_data, t_player *player);
int			get_minimap_range(t_map *map_data);
int			calculate_opacity(int tile_size, t_fpoint pixel, t_player *player);
int			*get_tile_texture(t_point tile, char **map, \
				int tex_count, int **textures);

void	render_minimap(t_player *player, t_vars *vars, t_map *map_data)
{
	t_fpoint	map;
	int			range;

	range = get_minimap_range(map_data);
	map_data->tile_size = MINIMAP_SIZE / range;
	map.x = player->pos_x - (float)range / 2;
	if (map.x < 0)
		map.x = 0;
	if (map.x + range > map_data->width)
		map.x = map_data->width - range;
	map.y = player->pos_y - (float)range / 2;
	if (map.y < 0)
		map.y = 0;
	if (map.y + range > map_data->height)
		map.y = map_data->height - range;
	draw_border(0, 0, 0x808080, &vars->img);
	draw_minimap(map, range, map_data, vars);
	draw_player(player, map, map_data, vars);
}

static void	draw_border(int x, int y, int border_color, t_img *img)
{
	int	draw_x;
	int	draw_y;
	int	border_end;

	border_end = MINIMAP_SIZE + (MINIMAP_OFFSET * 2);
	draw_y = 0;
	while (draw_y < border_end)
	{
		draw_x = 0;
		while (draw_x < border_end)
		{
			if (draw_y < MINIMAP_OFFSET || draw_y >= MINIMAP_SIZE || \
				draw_x < MINIMAP_OFFSET || draw_x >= MINIMAP_SIZE)
			{
				put_pixel(x + draw_x, y + draw_y, border_color, img);
			}
			draw_x++;
		}
		draw_y++;
	}
}

static void	draw_minimap(t_fpoint map, int range, t_map *map_data, t_vars *vars)
{
	t_point		screen;
	t_fpoint	pixel;
	t_point		tile;
	int			tile_size;
	int			color;

	tile_size = map_data->tile_size;
	pixel.y = map.y * tile_size;
	while (pixel.y < (map.y + range) * tile_size)
	{
		pixel.x = map.x * tile_size;
		while (pixel.x < (map.x + range) * tile_size)
		{
			screen.x = (int)pixel.x - map.x * tile_size + MINIMAP_OFFSET;
			screen.y = (int)pixel.y - map.y * tile_size + MINIMAP_OFFSET;
			tile.x = pixel.x / tile_size;
			tile.y = pixel.y / tile_size;
			color = get_pixel_color(tile, pixel, map_data, vars->player);
			put_pixel(screen.x, screen.y, color, &vars->img);
			pixel.x++;
		}
		pixel.y++;
	}
}

static int	get_pixel_color(t_point tile, t_fpoint pixel, \
		t_map *map_data, t_player *player)
{
	t_point	tex;
	int		color;
	int		tile_size;
	int		opacity;
	int		*texture;

	tile_size = map_data->tile_size;
	tex.x = ((int)pixel.x % tile_size) * map_data->tex_width / tile_size;
	tex.y = ((int)pixel.y % tile_size) * map_data->tex_height / tile_size;
	texture = get_tile_texture(tile, map_data->map, \
		map_data->texture_count, map_data->texture);
	if (texture == NULL)
		color = map_data->floor_color;
	else
		color = texture[tex.y * map_data->tex_width + tex.x];
	if (map_data->map[tile.y][tile.x] == '0' && texture != NULL)
		color = (color >> 1) & 8355711;
	opacity = calculate_opacity(tile_size, pixel, player);
	if (FULLBRIGHT == 0)
		color = apply_opacity(color, opacity);
	return (color);
}
