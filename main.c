/*  FUNCTIONS ALLOWED
open, close, read, write,
printf, malloc, free, perror,
strerror, exit, gettimeofday.
• All functions of the math
library (-lm man man 3 math).
• gettimeofday()
• All functions of the MinilibX
library. */

//all stuff to include
// # include <stdlib.h>
//# include <errno.h>
//# include <stdio.h>
//# include <mlx.h>
// # include "minilibx-linux/mlx.h"
//# include <unistd.h>
//# include <fcntl.h>
//# include "libft/libft.h"

#include "cub3d.h"

int	destroy_everything(t_mlx *data)
{
	/* if (data->shroom_image)
		mlx_destroy_image(data->mlx, data->shroom_image); */
	if (data->window)
		mlx_destroy_window(data->mlx, data->window);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		//free(data->mlx);
	}
/* 	if (data->map)
		free_map(data->map); */
	exit (0);
}

int main (void)
{
	t_mlx		data;

	data.mlx = mlx_init();
	if (!data.mlx)
		return 1; //errors("Allocation failed", data);
		
	data.window = mlx_new_window(data.mlx, 600, 600, "Cub3d");
	mlx_hook(data.window, 17, 0, destroy_everything, &data);
	mlx_loop(data.mlx);
	//parsing();
	//execution();
}





// TO COMPILE SO FAR
//cc main.c -L./minilibx-linux -I./minilibx-linux -lmlx -lXext -lX11 -lm && ./a.out