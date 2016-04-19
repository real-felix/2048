#include "game_2048.h"

#include <stdlib.h>

static int	grid_space_avaible(t_2048 *grid, int x, int y)
{
	while (y < grid->grid_size)
	{
		while (x < grid->grid_size)
		{
			if (grid->grid[y][x] == 0)
				return (1);
			x++;
		}
		x = 0;
		y++;
	}
	return (0);
}

int			grid_rand(t_2048 *grid, int rand_nb)
{
	int		i;
	int		xy[2];
	int		square_rand;
	int		ret;

	ret = 0;
	i = 0;
	xy[0] = -1;
	xy[1] = -1;
	while (i < rand_nb && grid_space_avaible(grid, 0, 0))
	{
		while ((grid->grid)[xy[1]][xy[0]] || *xy == -1)
		{
			xy[0] = rand() % (grid->grid_size);
			xy[1] = rand() % (grid->grid_size);
		}
		square_rand = 0;
		while (!IS_SQUARE(square_rand) || square_rand < 2)
			square_rand = rand() % (grid->grid_max_rand + 1);
		(grid->grid)[xy[1]][xy[0]] = square_rand;
		grid->score += square_rand;
		ret++;
		i++;
	}
	return (ret);
}
