#include "cub3d.h"

int **copy_map(int **src, int h_map, int w_map)
{
	int **copy = (int **)malloc(sizeof(int *) * h_map);
	if (!copy)
	{
		return NULL;
	}

	int i = 0;
	while (i < h_map)
	{
		copy[i] = (int *)malloc(sizeof(int) * w_map);
		if (!copy[i])
		{
			while (i > 0)
			{
				i--;
				free(copy[i]);
			}
			free(copy);
			return NULL;
		}

		int j = 0;
		while (j < w_map)
		{
			copy[i][j] = src[i][j];
			j++;
		}
		i++;
	}
	return copy;
}
