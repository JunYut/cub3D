/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:58:42 by tjun-yu           #+#    #+#             */
/*   Updated: 2025/02/13 13:41:42 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Libft.h>

#include "error.h"
#include "map.h"

void	get_spawn(t_list *map, int *spawn)
{
	char	*line;
	int		i;
	int		j;

	map = skip_empty_lines(map);
	i = -1;
	while (map)
	{
		i += 1;
		line = map->content;
		j = -1;
		while (line[++j])
		{
			if (ft_strchr(SPAWN_IDEN, line[j]))
			{
				spawn[0] = i;
				spawn[1] = j;
				spawn[2] = line[j];
				line[j] = '0';
				return ;
			}
		}
		map = map->next;
	}
	if (!ft_strchr(SPAWN_IDEN, spawn[2]))
		error_exit("Invalid spawn point");
}
