/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riceset <tkomeno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 19:04:32 by riceset           #+#    #+#             */
/*   Updated: 2024/07/04 19:04:40 by riceset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_textures(t_texture *textures[4])
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (textures[i] != NULL)
		{
			free(textures[i]->data);
			free(textures[i]);
		}
		i++;
	}
}

void	load_textures(t_data *data, t_texture *textures[4])
{
	int	i;

	i = 0;
	while (i < 4)
	{
		textures[i] = load_texture_from_bmp(extract_filename(data->texture[i]));
		if (textures[i] == NULL)
			ft_exit("Failed to load texture", data);
		i++;
	}
}
