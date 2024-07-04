/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_filename.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@tokyo.42.school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:22:09 by hhagiwar          #+#    #+#             */
/*   Updated: 2024/07/02 17:16:20 by riceset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*extract_filename(char *path)
{
	char	*filename;
	size_t	len;

	filename = ft_strrchr(path, '/');
	if (filename == NULL)
		filename = path;
	else
		filename++;
	len = ft_strlen(filename);
	if (len > 0 && filename[len - 1] == '\n')
		filename[len - 1] = '\0';
	return (filename);
}
