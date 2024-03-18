
#include "cub3d.h"

int main(int argc, char **argv)
{
	t_data *data;

	(void)data;
	if (argc == 2)
	{
		if (extension_check(argv[1]) == ERROR)
			ft_exit("File extension must be .cub", NULL);
		data = init_data(argv);
		start_game(data);
	}
	else
		ft_exit("Error: Invalid command line arguments. \nUsage: ./cub3D <path_to_map_file.cub>", NULL);
	exit(EXIT_SUCCESS);
}

__attribute__((destructor)) static void destructor()
{
	printf("\n--------- destructor ---------\n\n");
	system("leaks -q cub3d");
	printf("\n--------- End of destructor ---------\n\n");
}
